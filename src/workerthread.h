/**
 * @file workerthread.h
 * @brief Klasa wątku roboczego dla operacji w tle
 * @author PyScript AI Generator Team
 * @date 2026-03-25
 */

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QString>
#include "ollamaclient.h"
#include "pythonexecutor.h"

/**
 * @class WorkerThread
 * @brief Klasa wątku roboczego do obsługi generowania i wykonywania kodu
 * 
 * Używa QThread do wykonywania długotrwałych operacji (wywołania API, 
 * wykonanie kodu) bez blokowania GUI.
 */
class WorkerThread : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * @param prompt Prompt użytkownika
     * @param parent Wskaźnik do obiektu rodzica
     */
    explicit WorkerThread(const QString &prompt, QObject *parent = nullptr);
    
    /**
     * @brief Destruktor
     */
    ~WorkerThread();
    
    /**
     * @brief Zatrzymuje wątek
     */
    void stopThread();

signals:
    /**
     * @brief Sygnał emitowany po wygenerowaniu kodu
     * @param code Wygenerowany kod Python
     */
    void codeGenerated(const QString &code);
    
    /**
     * @brief Sygnał emitowany po wykonaniu kodu
     * @param output Wynik wykonania
     */
    void executionFinished(const QString &output);
    
    /**
     * @brief Sygnał emitowany w przypadku błędu
     * @param error Komunikat błędu
     */
    void errorOccurred(const QString &error);
    
    /**
     * @brief Sygnał informujący o postępie
     * @param message Komunikat o postępie
     */
    void progressUpdate(const QString &message);

protected:
    /**
     * @brief Główna funkcja wątku
     */
    void run() override;

private slots:
    /**
     * @brief Slot wywoływany po otrzymaniu kodu z API
     * @param code Wygenerowany kod
     */
    void onCodeReceived(const QString &code);
    
    /**
     * @brief Slot wywoływany po zakończeniu wykonywania
     * @param output Wynik
     */
    void onExecutionDone(const QString &output);
    
    /**
     * @brief Slot wywoływany w przypadku błędu generowania
     * @param error Komunikat błędu
     */
    void onGenerationError(const QString &error);
    
    /**
     * @brief Slot wywoływany w przypadku błędu wykonania
     * @param error Komunikat błędu
     */
    void onExecutionErrorSlot(const QString &error);

private:
    QString m_prompt; ///< Prompt użytkownika
    OllamaClient *m_ollamaClient; ///< Klient Ollama API
    PythonExecutor *m_pythonExecutor; ///< Executor kodu Python
    bool m_shouldStop; ///< Flaga zatrzymania wątku
    QString m_generatedCode; ///< Wygenerowany kod
};

#endif // WORKERTHREAD_H
