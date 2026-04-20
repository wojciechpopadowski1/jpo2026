/**
 * @file mainwindow.cpp
 * @brief Implementacja klasy MainWindow
 * @author PyScript AI Generator Team
 * @date 2026-03-25
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_workerThread(nullptr)
{
    ui->setupUi(this);
    
    // Początkowa konfiguracja GUI
    setGuiEnabled(true);
    ui->codeOutputText->setReadOnly(true);
    ui->executionOutputText->setReadOnly(true);
    
    // Ustawienie placeholder text
    ui->promptInput->setPlaceholderText("Wpisz opis zadania, np. 'oblicz sumę liczb od 1 do 100' lub 'wygeneruj wykres funkcji sin(x)'");
    
    setupConnections();
    
    ui->statusbar->showMessage("Gotowy do pracy", 3000);
    qDebug() << "MainWindow: Zainicjalizowano okno główne";
}

MainWindow::~MainWindow()
{
    if (m_workerThread) {
        m_workerThread->stopThread();
        m_workerThread->wait();
        delete m_workerThread;
    }
    delete ui;
    qDebug() << "MainWindow: Zniszczono okno główne";
}

void MainWindow::setupConnections()
{
    connect(ui->generateButton, &QPushButton::clicked,
            this, &MainWindow::onGenerateButtonClicked);
}

void MainWindow::onGenerateButtonClicked()
{
    QString prompt = ui->promptInput->toPlainText().trimmed();
    
    if (prompt.isEmpty()) {
        showErrorMessage("Błąd", "Proszę wpisać opis zadania!");
        return;
    }
    
    // Wyczyść poprzednie wyniki
    ui->codeOutputText->clear();
    ui->executionOutputText->clear();
    
    // Wyłącz GUI podczas przetwarzania
    setGuiEnabled(false);
    ui->statusbar->showMessage("Generowanie kodu...");
    
    qDebug() << "MainWindow: Rozpoczęcie generowania kodu dla promptu:" << prompt;
    
    // Utwórz i uruchom wątek roboczy
    m_workerThread = new WorkerThread(prompt, this);
    
    connect(m_workerThread, &WorkerThread::codeGenerated,
            this, &MainWindow::onCodeGenerated);
    connect(m_workerThread, &WorkerThread::executionFinished,
            this, &MainWindow::onExecutionFinished);
    connect(m_workerThread, &WorkerThread::errorOccurred,
            this, &MainWindow::onErrorOccurred);
    connect(m_workerThread, &WorkerThread::progressUpdate,
            this, &MainWindow::onProgressUpdate);
    connect(m_workerThread, &WorkerThread::finished,
            this, &MainWindow::onThreadFinished);
    
    m_workerThread->start();
}

void MainWindow::onCodeGenerated(const QString &code)
{
    qDebug() << "MainWindow: Otrzymano wygenerowany kod";
    ui->codeOutputText->setPlainText(code);
    ui->statusbar->showMessage("Kod wygenerowany, wykonywanie...");
}

void MainWindow::onExecutionFinished(const QString &output)
{
    qDebug() << "MainWindow: Otrzymano wynik wykonania";
    ui->executionOutputText->setPlainText(output);
    ui->statusbar->showMessage("Wykonanie zakończone pomyślnie!", 5000);
}

void MainWindow::onErrorOccurred(const QString &error)
{
    qDebug() << "MainWindow: Błąd:" << error;
    showErrorMessage("Błąd", error);
    ui->statusbar->showMessage("Wystąpił błąd", 5000);
}

void MainWindow::onProgressUpdate(const QString &message)
{
    ui->statusbar->showMessage(message);
    qDebug() << "MainWindow: Postęp:" << message;
}

void MainWindow::onThreadFinished()
{
    qDebug() << "MainWindow: Wątek zakończony";
    setGuiEnabled(true);
    
    if (m_workerThread) {
        m_workerThread->deleteLater();
        m_workerThread = nullptr;
    }
}

void MainWindow::setGuiEnabled(bool enabled)
{
    ui->promptInput->setEnabled(enabled);
    ui->generateButton->setEnabled(enabled);
}

void MainWindow::showErrorMessage(const QString &title, const QString &message)
{
    QMessageBox::critical(this, title, message);
}
