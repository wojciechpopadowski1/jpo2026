/**
 * @file ollamaclient.cpp
 * @brief Implementacja klasy OllamaClient
 * @author PyScript AI Generator Team
 * @date 2026-03-25
 */

#include "ollamaclient.h"
#include "config.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QDebug>
#include <QPointer>

OllamaClient::OllamaClient(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_currentReply(nullptr)
{
    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &OllamaClient::onReplyFinished);
    
    qDebug() << "OllamaClient: Zainicjalizowano";
}

OllamaClient::~OllamaClient()
{
    if (m_currentReply) {
        m_currentReply->disconnect();
        m_currentReply->abort();
        m_currentReply->deleteLater();
    }
    qDebug() << "OllamaClient: Zniszczono";
}

void OllamaClient::generateCode(const QString &prompt, const QString &model)
{
    if (prompt.trimmed().isEmpty()) {
        emit errorOccurred("Prompt nie może być pusty!");
        return;
    }
    
    // Anuluj poprzednie żądanie jeśli istnieje
    if (m_currentReply) {
        m_currentReply->abort();
        m_currentReply->deleteLater();
        m_currentReply = nullptr;
    }
    
    QString modelToUse = model.isEmpty() ? Config::DEFAULT_MODEL : model;
    
    emit progressUpdate("Połączenie z Ollama API...");
    qDebug() << "OllamaClient: Wysyłanie promptu do modelu" << modelToUse;
    
    // Przygotowanie żądania
    QJsonObject requestJson = createRequestJson(prompt, modelToUse);
    QJsonDocument doc(requestJson);
    QByteArray jsonData = doc.toJson();
    
    QNetworkRequest request;
    request.setUrl(QUrl(Config::OLLAMA_API_URL));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setTransferTimeout(Config::NETWORK_TIMEOUT);
    
    // Wysyłanie POST
    m_currentReply = m_networkManager->post(request, jsonData);
    
    emit progressUpdate("Oczekiwanie na odpowiedź z API...");
}

void OllamaClient::cancelRequest()
{
    if (m_currentReply) {
        qDebug() << "OllamaClient: Anulowanie żądania";
        m_currentReply->disconnect();
        m_currentReply->abort();
        m_currentReply->deleteLater();
        m_currentReply = nullptr;
    }
}

void OllamaClient::onReplyFinished(QNetworkReply *reply)
{
    if (reply != m_currentReply) {
        reply->deleteLater();
        return;
    }
    
    m_currentReply = nullptr;
    
    // Obsługa błędów sieciowych
    if (reply->error() != QNetworkReply::NoError) {
        QString errorMsg;
        if (reply->error() == QNetworkReply::ConnectionRefusedError) {
            errorMsg = "Błąd: Nie można połączyć się z Ollama API. Upewnij się, że Ollama jest uruchomiona (http://localhost:11434).";
        } else if (reply->error() == QNetworkReply::TimeoutError) {
            errorMsg = "Błąd: Przekroczono limit czasu połączenia. Spróbuj ponownie.";
        } else {
            errorMsg = QString("Błąd sieci: %1").arg(reply->errorString());
        }
        
        qDebug() << "OllamaClient:" << errorMsg;
        emit errorOccurred(errorMsg);
        reply->deleteLater();
        return;
    }
    
    // Odczytanie odpowiedzi
    QByteArray responseData = reply->readAll();
    reply->deleteLater();
    
    qDebug() << "OllamaClient: Otrzymano odpowiedź (" << responseData.size() << "bajtów)";
    
    // Parsowanie JSON
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(responseData, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        QString errorMsg = QString("Błąd parsowania JSON: %1").arg(parseError.errorString());
        qDebug() << "OllamaClient:" << errorMsg;
        emit errorOccurred(errorMsg);
        return;
    }
    
    QJsonObject jsonObj = doc.object();
    
    // Wydobycie kodu z odpowiedzi
    if (jsonObj.contains("response")) {
        QString code = jsonObj["response"].toString().trimmed();
        
        // Usunięcie ewentualnych znaczników markdown
        if (code.startsWith("```python")) {
            code = code.mid(9); // Usuń ```python
        }
        if (code.startsWith("```")) {
            code = code.mid(3); // Usuń ```
        }
        if (code.endsWith("```")) {
            code = code.left(code.length() - 3); // Usuń końcowe ```
        }
        code = code.trimmed();
        
        if (code.isEmpty()) {
            emit errorOccurred("Otrzymano pusty kod z API!");
            return;
        }
        
        qDebug() << "OllamaClient: Wygenerowano kod (" << code.length() << "znaków)";
        emit progressUpdate("Kod wygenerowany pomyślnie!");
        emit codeGenerated(code);
    } else {
        QString errorMsg = "Brak pola 'response' w odpowiedzi API";
        qDebug() << "OllamaClient:" << errorMsg;
        emit errorOccurred(errorMsg);
    }
}

QJsonObject OllamaClient::createRequestJson(const QString &prompt, const QString &model)
{
    QJsonObject json;
    json["model"] = model;
    json["prompt"] = prompt;
    json["system"] = Config::SYSTEM_PROMPT;
    json["stream"] = false;
    
    return json;
}
