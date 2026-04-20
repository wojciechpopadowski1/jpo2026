/**
 * @file main.cpp
 * @brief Punkt wejścia aplikacji PyScript AI Generator
 * @author PyScript AI Generator Team
 * @date 2026-03-25
 */

#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

/**
 * @brief Główna funkcja programu
 * @param argc Liczba argumentów
 * @param argv Argumenty wiersza poleceń
 * @return Kod wyjścia aplikacji
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Ustawienie informacji o aplikacji
    app.setApplicationName("PyScript AI Generator");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("PyScript Team");
    
    qDebug() << "Uruchamianie aplikacji PyScript AI Generator...";
    
    MainWindow window;
    window.setWindowTitle("PyScript AI Generator");
    window.show();
    
    return app.exec();
}
