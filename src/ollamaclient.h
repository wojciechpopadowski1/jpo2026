/**
 * @file ollamaclient.h
 * @brief Klasa do komunikacji z Ollama API
 * @author PyScript AI Generator Team
 * @date 2026-03-25
 */

#ifndef OLLAMACLIENT_H
#define OLLAMACLIENT_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QPointer>

/**
 * @class OllamaClient
 * @brief Klasa odpowiedzialna za komunikację z Ollama API przez REST
 * 
 * Umożliwia wysyłanie promptów do modelu językowego Ollama
 * i odbieranie wygenerowanego kodu Python.
 */
class OllamaClient : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * @param parent Wskaźnik do obiektu rodzica
     */
    explicit OllamaClient(QObject *parent = nullptr);
    
    /**
     * @brief Destruktor
     */
    ~OllamaClient();
    
    /**
     * @brief Wysyła prompt do Ollama API
     * @param prompt Opis zadania od użytkownika
     * @param model Nazwa modelu (domyślnie z config.h)
     */
    void generateCode(const QString &prompt, const QString &model = "");
    
    /**
     * @brief Anuluje bieżące żądanie
     */
    void cancelRequest();

signals:
    /**
     * @brief Sygnał emitowany po otrzymaniu kodu
     * @param code Wygenerowany kod Python
     */
    void codeGenerated(const QString &code);
    
    /**
     * @brief Sygnał emitowany w przypadku błędu
     * @param error Opis błędu
     */
    void errorOccurred(const QString &error);
    
    /**
     * @brief Sygnał informujący o postępie
     * @param message Komunikat o postępie
     */
    void progressUpdate(const QString &message);

private slots:
    /**
     * @brief Slot wywoływany po zakończeniu żądania HTTP
     * @param reply Odpowiedź z serwera
     */
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager; ///< Menedżer połączeń sieciowych
    QPointer<QNetworkReply> m_currentReply; ///< Aktualne żądanie HTTP
    
    /**
     * @brief Tworzy JSON z żądaniem do API
     * @param prompt Prompt użytkownika
     * @param model Nazwa modelu
     * @return QJsonObject z danymi żądania
     */
    QJsonObject createRequestJson(const QString &prompt, const QString &model);
};

#endif // OLLAMACLIENT_H
