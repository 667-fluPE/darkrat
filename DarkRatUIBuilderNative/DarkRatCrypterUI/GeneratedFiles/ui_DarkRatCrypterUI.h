/********************************************************************************
** Form generated from reading UI file 'DarkRatCrypterUI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DARKRATCRYPTERUI_H
#define UI_DARKRATCRYPTERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DarkRatCrypterUIClass
{
public:
    QWidget *centralWidget;
    QPushButton *build;
    QLineEdit *pastebinurl;
    QLineEdit *mutex;
    QLineEdit *encryptionkey;
    QPushButton *gen_mutex;
    QPushButton *gen_enckey;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *startup;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DarkRatCrypterUIClass)
    {
        if (DarkRatCrypterUIClass->objectName().isEmpty())
            DarkRatCrypterUIClass->setObjectName(QString::fromUtf8("DarkRatCrypterUIClass"));
        DarkRatCrypterUIClass->setWindowModality(Qt::NonModal);
        DarkRatCrypterUIClass->resize(390, 263);
        DarkRatCrypterUIClass->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(DarkRatCrypterUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        build = new QPushButton(centralWidget);
        build->setObjectName(QString::fromUtf8("build"));
        build->setGeometry(QRect(10, 150, 371, 51));
        pastebinurl = new QLineEdit(centralWidget);
        pastebinurl->setObjectName(QString::fromUtf8("pastebinurl"));
        pastebinurl->setGeometry(QRect(10, 30, 241, 20));
        mutex = new QLineEdit(centralWidget);
        mutex->setObjectName(QString::fromUtf8("mutex"));
        mutex->setGeometry(QRect(10, 70, 241, 20));
        encryptionkey = new QLineEdit(centralWidget);
        encryptionkey->setObjectName(QString::fromUtf8("encryptionkey"));
        encryptionkey->setGeometry(QRect(10, 110, 241, 20));
        gen_mutex = new QPushButton(centralWidget);
        gen_mutex->setObjectName(QString::fromUtf8("gen_mutex"));
        gen_mutex->setGeometry(QRect(260, 70, 75, 23));
        gen_enckey = new QPushButton(centralWidget);
        gen_enckey->setObjectName(QString::fromUtf8("gen_enckey"));
        gen_enckey->setGeometry(QRect(260, 110, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 131, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 47, 13));
        startup = new QCheckBox(centralWidget);
        startup->setObjectName(QString::fromUtf8("startup"));
        startup->setGeometry(QRect(260, 30, 111, 17));
        startup->setStyleSheet(QString::fromUtf8(""));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 90, 91, 16));
        DarkRatCrypterUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DarkRatCrypterUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 390, 21));
        DarkRatCrypterUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DarkRatCrypterUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DarkRatCrypterUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DarkRatCrypterUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DarkRatCrypterUIClass->setStatusBar(statusBar);

        retranslateUi(DarkRatCrypterUIClass);

        QMetaObject::connectSlotsByName(DarkRatCrypterUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *DarkRatCrypterUIClass)
    {
        DarkRatCrypterUIClass->setWindowTitle(QApplication::translate("DarkRatCrypterUIClass", "DarkRatCrypterUI", nullptr));
        build->setText(QApplication::translate("DarkRatCrypterUIClass", "Build", nullptr));
        gen_mutex->setText(QApplication::translate("DarkRatCrypterUIClass", "PushButton", nullptr));
        gen_enckey->setText(QApplication::translate("DarkRatCrypterUIClass", "PushButton", nullptr));
        label->setText(QApplication::translate("DarkRatCrypterUIClass", "Pastebin URL", nullptr));
        label_2->setText(QApplication::translate("DarkRatCrypterUIClass", "Mutex", nullptr));
        startup->setText(QApplication::translate("DarkRatCrypterUIClass", "Enable Startup", nullptr));
        label_3->setText(QApplication::translate("DarkRatCrypterUIClass", "Encryption Key", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DarkRatCrypterUIClass: public Ui_DarkRatCrypterUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DARKRATCRYPTERUI_H
