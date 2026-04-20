/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionWyjscie;
    QAction *actionOProgramie;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *promptLabel;
    QPlainTextEdit *promptInput;
    QPushButton *generateButton;
    QLabel *codeLabel;
    QPlainTextEdit *codeOutputText;
    QLabel *executionLabel;
    QPlainTextEdit *executionOutputText;
    QMenuBar *menubar;
    QMenu *menuPlik;
    QMenu *menuPomoc;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 700);
        actionWyjscie = new QAction(MainWindow);
        actionWyjscie->setObjectName("actionWyjscie");
        actionOProgramie = new QAction(MainWindow);
        actionOProgramie->setObjectName("actionOProgramie");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");

        verticalLayout->addWidget(titleLabel);

        promptLabel = new QLabel(centralwidget);
        promptLabel->setObjectName("promptLabel");

        verticalLayout->addWidget(promptLabel);

        promptInput = new QPlainTextEdit(centralwidget);
        promptInput->setObjectName("promptInput");
        promptInput->setMaximumSize(QSize(16777215, 100));

        verticalLayout->addWidget(promptInput);

        generateButton = new QPushButton(centralwidget);
        generateButton->setObjectName("generateButton");
        generateButton->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        generateButton->setFont(font);

        verticalLayout->addWidget(generateButton);

        codeLabel = new QLabel(centralwidget);
        codeLabel->setObjectName("codeLabel");

        verticalLayout->addWidget(codeLabel);

        codeOutputText = new QPlainTextEdit(centralwidget);
        codeOutputText->setObjectName("codeOutputText");
        codeOutputText->setReadOnly(true);

        verticalLayout->addWidget(codeOutputText);

        executionLabel = new QLabel(centralwidget);
        executionLabel->setObjectName("executionLabel");

        verticalLayout->addWidget(executionLabel);

        executionOutputText = new QPlainTextEdit(centralwidget);
        executionOutputText->setObjectName("executionOutputText");
        executionOutputText->setReadOnly(true);

        verticalLayout->addWidget(executionOutputText);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 22));
        menuPlik = new QMenu(menubar);
        menuPlik->setObjectName("menuPlik");
        menuPomoc = new QMenu(menubar);
        menuPomoc->setObjectName("menuPomoc");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuPlik->menuAction());
        menubar->addAction(menuPomoc->menuAction());
        menuPlik->addAction(actionWyjscie);
        menuPomoc->addAction(actionOProgramie);

        retranslateUi(MainWindow);
        QObject::connect(actionWyjscie, &QAction::triggered, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PyScript AI Generator", nullptr));
        actionWyjscie->setText(QCoreApplication::translate("MainWindow", "Wyj\305\233cie", nullptr));
#if QT_CONFIG(shortcut)
        actionWyjscie->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOProgramie->setText(QCoreApplication::translate("MainWindow", "O programie", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:700;\">PyScript AI Generator</span></p></body></html>", nullptr));
        promptLabel->setText(QCoreApplication::translate("MainWindow", "Opis zadania (po polsku lub angielsku):", nullptr));
        generateButton->setText(QCoreApplication::translate("MainWindow", "\360\237\232\200 Generuj i Wykonaj", nullptr));
        codeLabel->setText(QCoreApplication::translate("MainWindow", "Wygenerowany kod Python:", nullptr));
        codeOutputText->setPlainText(QString());
        executionLabel->setText(QCoreApplication::translate("MainWindow", "Wynik wykonania:", nullptr));
        executionOutputText->setPlainText(QString());
        menuPlik->setTitle(QCoreApplication::translate("MainWindow", "Plik", nullptr));
        menuPomoc->setTitle(QCoreApplication::translate("MainWindow", "Pomoc", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
