/**
 * @file pythonexecutor.cpp
 * @brief Implementacja klasy PythonExecutor
 * @author PyScript AI Generator Team
 * @date 2026-03-25
 */

#include "pythonexecutor.h"
#include "config.h"
#include <QTemporaryFile>
#include <QFile>
#include <QDebug>
#include <QDir>

PythonExecutor::PythonExecutor(QObject *parent)
    : QObject(parent)
    , m_process(new QProcess(this))
    , m_tempFilePath()
{
    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &PythonExecutor::onProcessFinished);
    connect(m_process, &QProcess::errorOccurred,
            this, &PythonExecutor::onProcessError);
    
    qDebug() << "PythonExecutor: Zainicjalizowano";
}

PythonExecutor::~PythonExecutor()
{
    if (m_process->state() != QProcess::NotRunning) {
        m_process->kill();
        m_process->waitForFinished();
    }
    removeTempFile();
    qDebug() << "PythonExecutor: Zniszczono";
}

void PythonExecutor::executeCode(const QString &code)
{
    if (code.trimmed().isEmpty()) {
        emit executionError("Kod nie może być pusty!");
        return;
    }
    
    // Zatrzymaj poprzednie wykonanie
    if (m_process->state() != QProcess::NotRunning) {
        m_process->kill();
        m_process->waitForFinished();
    }
    
    emit progressUpdate("Przygotowywanie wykonania kodu...");
    qDebug() << "PythonExecutor: Rozpoczęcie wykonywania kodu";
    
    // Utworzenie tymczasowego pliku
    m_tempFilePath = createTempFile(code);
    if (m_tempFilePath.isEmpty()) {
        emit executionError("Nie można utworzyć tymczasowego pliku!");
        return;
    }
    
    qDebug() << "PythonExecutor: Plik tymczasowy:" << m_tempFilePath;
    
    // Uruchomienie Python
    QStringList arguments;
    arguments << m_tempFilePath;
    
    emit progressUpdate("Wykonywanie kodu Python...");
    m_process->start(Config::PYTHON_EXECUTABLE, arguments);
    
    if (!m_process->waitForStarted(5000)) {
        QString errorMsg = "Nie można uruchomić interpretera Python. Upewnij się, że Python jest zainstalowany.";
        qDebug() << "PythonExecutor:" << errorMsg;
        emit executionError(errorMsg);
        removeTempFile();
    }
}

void PythonExecutor::stopExecution()
{
    if (m_process->state() != QProcess::NotRunning) {
        qDebug() << "PythonExecutor: Zatrzymywanie wykonywania";
        m_process->kill();
        m_process->waitForFinished();
        removeTempFile();
    }
}

void PythonExecutor::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "PythonExecutor: Proces zakończony, kod wyjścia:" << exitCode;
    
    QString output = QString::fromLocal8Bit(m_process->readAllStandardOutput());
    QString errors = QString::fromLocal8Bit(m_process->readAllStandardError());
    
    removeTempFile();
    
    if (exitStatus == QProcess::CrashExit) {
        QString errorMsg = "Proces Python został przerwany!\n\nBłąd:\n" + errors;
        qDebug() << "PythonExecutor: Crash:" << errors;
        emit executionError(errorMsg);
        return;
    }
    
    if (exitCode != 0 || !errors.isEmpty()) {
        QString errorMsg = "Błąd wykonania kodu Python!\n\n";
        if (!errors.isEmpty()) {
            errorMsg += "Błąd:\n" + errors;
        }
        if (!output.isEmpty()) {
            errorMsg += "\n\nWyjście:\n" + output;
        }
        qDebug() << "PythonExecutor:" << errorMsg;
        emit executionError(errorMsg);
        return;
    }
    
    if (output.isEmpty()) {
        output = "(Kod wykonał się pomyślnie, ale nie wygenerował żadnego wyjścia)";
    }
    
    qDebug() << "PythonExecutor: Wykonanie zakończone pomyślnie";
    emit progressUpdate("Kod wykonał się pomyślnie!");
    emit executionFinished(output);
}

void PythonExecutor::onProcessError(QProcess::ProcessError error)
{
    QString errorMsg;
    switch (error) {
        case QProcess::FailedToStart:
            errorMsg = "Nie można uruchomić interpretera Python. Sprawdź, czy Python jest zainstalowany i dostępny w PATH.";
            break;
        case QProcess::Crashed:
            errorMsg = "Proces Python został przerwany podczas wykonywania.";
            break;
        case QProcess::Timedout:
            errorMsg = "Przekroczono limit czasu wykonania.";
            break;
        case QProcess::WriteError:
            errorMsg = "Błąd zapisu do procesu.";
            break;
        case QProcess::ReadError:
            errorMsg = "Błąd odczytu z procesu.";
            break;
        default:
            errorMsg = "Nieznany błąd procesu.";
            break;
    }
    
    qDebug() << "PythonExecutor: Błąd procesu:" << errorMsg;
    removeTempFile();
    emit executionError(errorMsg);
}

QString PythonExecutor::createTempFile(const QString &code)
{
    try {
        // Utwórz katalog tymczasowy jeśli nie istnieje
        QDir tempDir = QDir::temp();
        
        // Utwórz unikalny plik
        QTemporaryFile tempFile(tempDir.filePath("pyscript_XXXXXX.py"));
        tempFile.setAutoRemove(false); // Nie usuwaj automatycznie
        
        if (!tempFile.open()) {
            qDebug() << "PythonExecutor: Nie można utworzyć pliku tymczasowego";
            return QString();
        }
        
        // Zapisz kod
        QTextStream stream(&tempFile);
        stream.setEncoding(QStringConverter::Utf8);
        stream << code;
        
        QString filePath = tempFile.fileName();
        tempFile.close();
        
        return filePath;
    } catch (const std::exception &e) {
        qDebug() << "PythonExecutor: Wyjątek podczas tworzenia pliku:" << e.what();
        return QString();
    }
}

void PythonExecutor::removeTempFile()
{
    if (!m_tempFilePath.isEmpty()) {
        QFile::remove(m_tempFilePath);
        qDebug() << "PythonExecutor: Usunięto plik tymczasowy:" << m_tempFilePath;
        m_tempFilePath.clear();
    }
}
