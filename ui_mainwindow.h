/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *RESULT1_2;
    QPushButton *getPicBtn;
    QLabel *STEP1;
    QComboBox *pictureSlct;
    QPushButton *getPathBtn;
    QTextBrowser *textBrowser;
    QComboBox *testSetSlct;
    QLabel *STEP2;
    QLineEdit *pathEdit;
    QPushButton *startCltBtn;
    QLabel *RESULT1;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(700, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        RESULT1_2 = new QLabel(centralwidget);
        RESULT1_2->setObjectName(QString::fromUtf8("RESULT1_2"));
        RESULT1_2->setGeometry(QRect(10, 250, 371, 31));
        getPicBtn = new QPushButton(centralwidget);
        getPicBtn->setObjectName(QString::fromUtf8("getPicBtn"));
        getPicBtn->setGeometry(QRect(540, 210, 141, 31));
        getPicBtn->setAutoDefault(false);
        STEP1 = new QLabel(centralwidget);
        STEP1->setObjectName(QString::fromUtf8("STEP1"));
        STEP1->setGeometry(QRect(10, 10, 311, 31));
        pictureSlct = new QComboBox(centralwidget);
        pictureSlct->setObjectName(QString::fromUtf8("pictureSlct"));
        pictureSlct->setGeometry(QRect(10, 210, 501, 31));
        getPathBtn = new QPushButton(centralwidget);
        getPathBtn->setObjectName(QString::fromUtf8("getPathBtn"));
        getPathBtn->setGeometry(QRect(540, 50, 141, 31));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 290, 671, 431));
        testSetSlct = new QComboBox(centralwidget);
        testSetSlct->setObjectName(QString::fromUtf8("testSetSlct"));
        testSetSlct->setGeometry(QRect(10, 130, 501, 31));
        STEP2 = new QLabel(centralwidget);
        STEP2->setObjectName(QString::fromUtf8("STEP2"));
        STEP2->setGeometry(QRect(10, 90, 301, 31));
        pathEdit = new QLineEdit(centralwidget);
        pathEdit->setObjectName(QString::fromUtf8("pathEdit"));
        pathEdit->setGeometry(QRect(10, 50, 501, 31));
        startCltBtn = new QPushButton(centralwidget);
        startCltBtn->setObjectName(QString::fromUtf8("startCltBtn"));
        startCltBtn->setGeometry(QRect(540, 130, 141, 31));
        startCltBtn->setAutoDefault(false);
        RESULT1 = new QLabel(centralwidget);
        RESULT1->setObjectName(QString::fromUtf8("RESULT1"));
        RESULT1->setGeometry(QRect(10, 170, 421, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 700, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        getPicBtn->setDefault(false);
        startCltBtn->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        RESULT1_2->setText(QCoreApplication::translate("MainWindow", "Result2.\350\256\241\347\256\227\350\277\207\347\250\213\357\274\232", nullptr));
        getPicBtn->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\350\267\257\345\276\204\345\233\276", nullptr));
        STEP1->setText(QCoreApplication::translate("MainWindow", "Step1.\350\257\267\350\276\223\345\205\245\346\240\207\345\207\206\351\233\206\347\233\256\345\275\225\357\274\232", nullptr));
        getPathBtn->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\346\240\207\345\207\206\351\233\206", nullptr));
        STEP2->setText(QCoreApplication::translate("MainWindow", "Step2.\351\200\211\346\213\251\346\240\207\345\207\206\351\233\206\345\271\266\350\256\241\347\256\227\357\274\232", nullptr));
        startCltBtn->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\274\224\345\214\226\350\256\241\347\256\227", nullptr));
        RESULT1->setText(QCoreApplication::translate("MainWindow", "Result1.\346\237\245\347\234\213\345\244\247\345\271\205\344\274\230\345\214\226\350\247\243\347\232\204\350\267\257\345\276\204\345\233\276\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
