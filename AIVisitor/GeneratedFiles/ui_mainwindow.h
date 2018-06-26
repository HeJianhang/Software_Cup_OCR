/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *fileButton;
    QTableView *tableView;
    QPushButton *checkButton;
    QPushButton *excelButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(700, 500);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        fileButton = new QPushButton(centralWidget);
        fileButton->setObjectName(QStringLiteral("fileButton"));
        fileButton->setGeometry(QRect(520, 210, 151, 31));
        QFont font1;
        font1.setPointSize(12);
        fileButton->setFont(font1);
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(20, 120, 461, 341));
        tableView->setBaseSize(QSize(0, 0));
        QFont font2;
        font2.setPointSize(10);
        tableView->setFont(font2);
        checkButton = new QPushButton(centralWidget);
        checkButton->setObjectName(QStringLiteral("checkButton"));
        checkButton->setGeometry(QRect(520, 280, 151, 31));
        checkButton->setFont(font1);
        excelButton = new QPushButton(centralWidget);
        excelButton->setObjectName(QStringLiteral("excelButton"));
        excelButton->setGeometry(QRect(520, 350, 151, 31));
        excelButton->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        fileButton->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", 0));
        checkButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\350\257\206\345\210\253", 0));
        excelButton->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220Excel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
