/**
 * @file workerthread.cpp
 * @brief Implementacja klasy WorkerThread
 * @author PyScript AI Generator Team
 * @date 2026-03-25
 */

#include "workerthread.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

WorkerThread::WorkerThread(const QString &prompt, QObject *parent)
    : QThread(parent)
    , m_prompt(prompt)
    , m_ollamaClient(nullptr)
    , m_pythonExecutor(nullptr)
    , m_shouldStop(false)
    , m_generatedCode()
{
    qDebug() << "WorkerThread: Utworzono wątek";
}

WorkerThread::~WorkerThread()
{
    stopThread();
    wait(); // Poczekaj aż wątek się zakończy
    qDebug() << "WorkerThread: Zniszczono wątek";
}

void WorkerThread::stopThread()
{
    qDebug() << "WorkerThread: Żądanie zatrzymania wątku";
    m_shouldStop = true;
    
    if (m_ollamaClient) {
        m_ollamaClient->cancelRequest();
    }
    
    if (m_pythonExecutor) {
        m_pythonExecutor->stopExecution();
    }
}

void WorkerThread::run()
{
    qDebug() << "WorkerThread: Wątek rozpoczął pracę";
    emit progressUpdate("Wątek roboczy uruchomiony...");
    
    // Utworzenie obiektów w kontekście wątku
    m_ollamaClient = new OllamaClient();
    m_pythonExecutor = new PythonExecutor();
    
    // Podłączenie sygnałów
    connect(m_ollamaClient, &OllamaClient::codeGenerated,
            this, &WorkerThread::onCodeReceived);
    connect(m_ollamaClient, &OllamaClient::errorOccurred,
            this, &WorkerThread::onGenerationError);
    connect(m_ollamaClient, &OllamaClient::progressUpdate,
            this, &WorkerThread::progressUpdate);
    
    connect(m_pythonExecutor, &PythonExecutor::executionFinished,
            this, &WorkerThread::onExecutionDone);
    connect(m_pythonExecutor, &PythonExecutor::executionError,
            this, &WorkerThread::onExecutionErrorSlot);
    connect(m_pythonExecutor, &PythonExecutor::progressUpdate,
            this, &WorkerThread::progressUpdate);
    
    // Uruchomienie generowania kodu
    if (!m_shouldStop) {
        m_ollamaClient->generateCode(m_prompt);
    }
    
    // Pętla zdarzeń wątku
    exec();
    
    // Sprzątanie
    delete m_ollamaClient;
    delete m_pythonExecutor;
    m_ollamaClient = nullptr;
    m_pythonExecutor = nullptr;
    
    qDebug() << "WorkerThread: Wątek zakończył pracę";
}

void WorkerThread::onCodeReceived(const QString &code)
{
    if (m_shouldStop) {
        quit();
        return;
    }
    
    qDebug() << "WorkerThread: Otrzymano kod";
    m_generatedCode = code;
    emit codeGenerated(code);
    
    // Automatyczne wykonanie kodu
    if (m_pythonExecutor && !m_shouldStop) {
        m_pythonExecutor->executeCode(code);
    } else {
        quit();
    }
}

void WorkerThread::onExecutionDone(const QString &output)
{
    qDebug() << "WorkerThread: Wykonanie zakończone";
    emit executionFinished(output);
    quit(); // Zakończ pętlę zdarzeń
}

void WorkerThread::onGenerationError(const QString &error)
{
    qDebug() << "WorkerThread: Błąd generowania:" << error;
    emit errorOccurred(error);
    quit();
}

void WorkerThread::onExecutionErrorSlot(const QString &error)
{
    qDebug() << "WorkerThread: Błąd wykonania:" << error;
    emit errorOccurred(error);
    quit();
}
