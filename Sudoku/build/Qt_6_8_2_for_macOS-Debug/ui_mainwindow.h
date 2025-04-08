/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *LearnSudoku;
    QStackedWidget *stackedWidget;
    QWidget *HomePage;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *Intro1;
    QLabel *label_2;
    QPushButton *pushButton_4;
    QWidget *Intro2;
    QLabel *label_7;
    QPushButton *pushButton_13;
    QWidget *HelpfulStrats;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        LearnSudoku = new QWidget(MainWindow);
        LearnSudoku->setObjectName("LearnSudoku");
        stackedWidget = new QStackedWidget(LearnSudoku);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 791, 531));
        HomePage = new QWidget();
        HomePage->setObjectName("HomePage");
        label = new QLabel(HomePage);
        label->setObjectName("label");
        label->setGeometry(QRect(240, 140, 311, 71));
        QFont font;
        font.setPointSize(50);
        label->setFont(font);
        pushButton = new QPushButton(HomePage);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(310, 220, 151, 41));
        QFont font1;
        font1.setPointSize(25);
        pushButton->setFont(font1);
        pushButton_2 = new QPushButton(HomePage);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(280, 270, 211, 41));
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(HomePage);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(310, 320, 151, 41));
        pushButton_3->setFont(font1);
        stackedWidget->addWidget(HomePage);
        Intro1 = new QWidget();
        Intro1->setObjectName("Intro1");
        label_2 = new QLabel(Intro1);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 10, 161, 41));
        QFont font2;
        font2.setPointSize(30);
        label_2->setFont(font2);
        pushButton_4 = new QPushButton(Intro1);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(640, 10, 100, 31));
        pushButton_4->setFont(font1);
        stackedWidget->addWidget(Intro1);
        Intro2 = new QWidget();
        Intro2->setObjectName("Intro2");
        label_7 = new QLabel(Intro2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 10, 161, 41));
        label_7->setFont(font2);
        pushButton_13 = new QPushButton(Intro2);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(640, 10, 100, 31));
        pushButton_13->setFont(font1);
        stackedWidget->addWidget(Intro2);
        HelpfulStrats = new QWidget();
        HelpfulStrats->setObjectName("HelpfulStrats");
        stackedWidget->addWidget(HelpfulStrats);
        MainWindow->setCentralWidget(LearnSudoku);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 36));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Learn Sudoku", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Introduction", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Helpful Strategies", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Techniques", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Introduction", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Introduction", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
