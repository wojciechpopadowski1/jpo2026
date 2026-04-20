/**
 * @file mainwindow.h
 * @brief Główne okno aplikacji PyScript AI Generator
 * @author PyScript AI Generator Team
 * @date 2026-03-25
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "workerthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Główne okno aplikacji z interfejsem użytkownika
 * 
 * Zawiera pola tekstowe do wpisania promptu, wyświetlenia kodu
 * i wyniku wykonania, oraz przyciski sterujące.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * @param parent Wskaźnik do obiektu rodzica
     */
    MainWindow(QWidget *parent = nullptr);
    
    /**
     * @brief Destruktor
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot wywoływany po kliknięciu przycisku "Generuj i Wykonaj"
     */
    void onGenerateButtonClicked();
    
    /**
     * @brief Slot wywoływany po otrzymaniu kodu z wątku
     * @param code Wygenerowany kod Python
     */
    void onCodeGenerated(const QString &code);
    
    /**
     * @brief Slot wywoływany po zakończeniu wykonywania kodu
     * @param output Wynik wykonania
     */
    void onExecutionFinished(const QString &output);
    
    /**
     * @brief Slot wywoływany w przypadku błędu
     * @param error Komunikat błędu
     */
    void onErrorOccurred(const QString &error);
    
    /**
     * @brief Slot wywoływany przy aktualizacji postępu
     * @param message Komunikat o postępie
     */
    void onProgressUpdate(const QString &message);
    
    /**
     * @brief Slot wywoływany po zakończeniu wątku
     */
    void onThreadFinished();

private:
    Ui::MainWindow *ui; ///< Interfejs użytkownika
    WorkerThread *m_workerThread; ///< Wątek roboczy
    
    /**
     * @brief Inicjalizuje połączenia sygnałów i slotów
     */
    void setupConnections();
    
    /**
     * @brief Ustawia stan GUI (aktywny/nieaktywny)
     * @param enabled True jeśli GUI ma być aktywne
     */
    void setGuiEnabled(bool enabled);
    
    /**
     * @brief Wyświetla komunikat błędu
     * @param title Tytuł okna
     * @param message Treść komunikatu
     */
    void showErrorMessage(const QString &title, const QString &message);
};

#endif // MAINWINDOW_H
