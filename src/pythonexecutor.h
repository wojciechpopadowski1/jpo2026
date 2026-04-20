/**
 * @file pythonexecutor.h
 * @brief Klasa do wykonywania kodu Python
 * @author PyScript AI Generator Team
 * @date 2026-03-25
 */

#ifndef PYTHONEXECUTOR_H
#define PYTHONEXECUTOR_H

#include <QObject>
#include <QString>
#include <QProcess>

/**
 * @class PythonExecutor
 * @brief Klasa odpowiedzialna za wykonywanie wygenerowanego kodu Python
 * 
 * Używa QProcess do uruchomienia interpretera Python i wykonania kodu.
 * Zwraca standardowe wyjście oraz błędy.
 */
class PythonExecutor : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * @param parent Wskaźnik do obiektu rodzica
     */
    explicit PythonExecutor(QObject *parent = nullptr);
    
    /**
     * @brief Destruktor
     */
    ~PythonExecutor();
    
    /**
     * @brief Wykonuje kod Python
     * @param code Kod Python do wykonania
     */
    void executeCode(const QString &code);
    
    /**
     * @brief Zatrzymuje wykonywanie kodu
     */
    void stopExecution();

signals:
    /**
     * @brief Sygnał emitowany po zakończeniu wykonywania
     * @param output Standardowe wyjście
     */
    void executionFinished(const QString &output);
    
    /**
     * @brief Sygnał emitowany w przypadku błędu wykonania
     * @param error Komunikat błędu
     */
    void executionError(const QString &error);
    
    /**
     * @brief Sygnał informujący o postępie
     * @param message Komunikat o postępie
     */
    void progressUpdate(const QString &message);

private slots:
    /**
     * @brief Slot wywoływany po zakończeniu procesu
     * @param exitCode Kod wyjścia procesu
     * @param exitStatus Status zakończenia
     */
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    
    /**
     * @brief Slot wywoływany w przypadku błędu procesu
     * @param error Typ błędu
     */
    void onProcessError(QProcess::ProcessError error);

private:
    QProcess *m_process; ///< Proces Python
    QString m_tempFilePath; ///< Ścieżka do tymczasowego pliku z kodem
    
    /**
     * @brief Tworzy tymczasowy plik z kodem
     * @param code Kod do zapisania
     * @return Ścieżka do pliku lub pusty string w przypadku błędu
     */
    QString createTempFile(const QString &code);
    
    /**
     * @brief Usuwa tymczasowy plik
     */
    void removeTempFile();
};

#endif // PYTHONEXECUTOR_H
