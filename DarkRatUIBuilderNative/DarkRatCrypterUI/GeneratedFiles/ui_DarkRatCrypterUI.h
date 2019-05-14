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
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
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
    QFrame *line;
    QLabel *icon;
    QLabel *icon_path;
    QPushButton *btn_icon;
    QFrame *line_2;
    QPushButton *btn_change_output;
    QLineEdit *outputname;
    QLabel *label_4;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DarkRatCrypterUIClass)
    {
        if (DarkRatCrypterUIClass->objectName().isEmpty())
            DarkRatCrypterUIClass->setObjectName(QString::fromUtf8("DarkRatCrypterUIClass"));
        DarkRatCrypterUIClass->setWindowModality(Qt::NonModal);
        DarkRatCrypterUIClass->resize(656, 252);
        DarkRatCrypterUIClass->setStyleSheet(QString::fromUtf8("/*\n"
"Material Dark Style Sheet for QT Applications\n"
"Author: Jaime A. Quiroga P.\n"
"Inspired on https://github.com/jxfwinter/qt-material-stylesheet\n"
"Company: GTRONICK\n"
"Last updated: 04/12/2018, 15:00.\n"
"Available at: https://github.com/GTRONICK/QSS/blob/master/MaterialDark.qss\n"
"*/\n"
"QMainWindow {\n"
"	background-color:#1e1d23;\n"
"}\n"
"QDialog {\n"
"	background-color:#1e1d23;\n"
"}\n"
"QColorDialog {\n"
"	background-color:#1e1d23;\n"
"}\n"
"QTextEdit {\n"
"	background-color:#1e1d23;\n"
"	color: #a9b7c6;\n"
"}\n"
"QPlainTextEdit {\n"
"	selection-background-color:#007b50;\n"
"	background-color:#1e1d23;\n"
"	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-bottom-color: transparent;\n"
"	border-width: 1px;\n"
"	color: #a9b7c6;\n"
"}\n"
"QPushButton{\n"
"	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-botto"
                        "m-color: transparent;\n"
"	border-width: 1px;\n"
"	border-style: solid;\n"
"	color: #a9b7c6;\n"
"	padding: 2px;\n"
"	background-color: #3b4045;\n"
"}\n"
"QPushButton::default{\n"
"	border-style: inset;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-bottom-color: #7d15ba;\n"
"	border-width: 1px;\n"
"	color: #a9b7c6;\n"
"	padding: 2px;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QToolButton {\n"
"	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-bottom-color: #7d15ba;\n"
"	border-bottom-width: 1px;\n"
"	border-style: solid;\n"
"	color: #a9b7c6;\n"
"	padding: 2px;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QToolButton:hover{\n"
"	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-bottom-color: #7d15ba;\n"
"	border-bottom-width: 2px;\n"
"	border-style: solid"
                        ";\n"
"	color: #FFFFFF;\n"
"	padding-bottom: 1px;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QPushButton:hover{\n"
"	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-bottom-color: #7d15ba;\n"
"	border-bottom-width: 1px;\n"
"	border-style: solid;\n"
"	color: #FFFFFF;\n"
"	padding-bottom: 2px;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QPushButton:pressed{\n"
"	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-bottom-color: #7d15ba;\n"
"	border-bottom-width: 2px;\n"
"	border-style: solid;\n"
"	color: #7d15ba;\n"
"	padding-bottom: 1px;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QPushButton:disabled{\n"
"	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-bottom-color: #808086;\n"
"	border-bottom-width: 2px;\n"
"	border-style: solid;\n"
"	co"
                        "lor: #808086;\n"
"	padding-bottom: 1px;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QLineEdit {\n"
"	border-width: 1px; border-radius: 4px;\n"
"	border-color: rgb(58, 58, 58);\n"
"	border-style: inset;\n"
"	padding: 0 8px;\n"
"	color: #a9b7c6;\n"
"	background:#1e1d23;\n"
"	selection-background-color:#007b50;\n"
"	selection-color: #FFFFFF;\n"
"}\n"
"QLabel {\n"
"	color: #a9b7c6;\n"
"}\n"
"QLCDNumber {\n"
"	color: #37e6b4;\n"
"}\n"
"QProgressBar {\n"
"	text-align: center;\n"
"	color: rgb(240, 240, 240);\n"
"	border-width: 1px; \n"
"	border-radius: 10px;\n"
"	border-color: rgb(58, 58, 58);\n"
"	border-style: inset;\n"
"	background-color:#1e1d23;\n"
"}\n"
"QProgressBar::chunk {\n"
"	background-color: #7d15ba;\n"
"	border-radius: 5px;\n"
"}\n"
"QMenuBar {\n"
"	background-color: #1e1d23;\n"
"}\n"
"QMenuBar::item {\n"
"	color: #a9b7c6;\n"
"  	spacing: 3px;\n"
"  	padding: 1px 4px;\n"
"  	background: #1e1d23;\n"
"}\n"
"\n"
"QMenuBar::item:selected {\n"
"  	background:#1e1d23;\n"
"	color: #FFFFFF;\n"
"}\n"
"QMenu::item:s"
                        "elected {\n"
"	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: #7d15ba;\n"
"	border-bottom-color: transparent;\n"
"	border-left-width: 2px;\n"
"	color: #FFFFFF;\n"
"	padding-left:15px;\n"
"	padding-top:4px;\n"
"	padding-bottom:4px;\n"
"	padding-right:7px;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QMenu::item {\n"
"	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-bottom-color: transparent;\n"
"	border-bottom-width: 1px;\n"
"	border-style: solid;\n"
"	color: #a9b7c6;\n"
"	padding-left:17px;\n"
"	padding-top:4px;\n"
"	padding-bottom:4px;\n"
"	padding-right:7px;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QMenu{\n"
"	background-color:#1e1d23;\n"
"}\n"
"QTabWidget {\n"
"	color:rgb(0,0,0);\n"
"	background-color:#1e1d23;\n"
"}\n"
"QTabWidget::pane {\n"
"		border-color: rgb(77,77,77);\n"
"		background-color:#1e1d23;\n"
"		border-style: solid;\n"
"		border-"
                        "width: 1px;\n"
"    	border-radius: 6px;\n"
"}\n"
"QTabBar::tab {\n"
"	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-bottom-color: transparent;\n"
"	border-bottom-width: 1px;\n"
"	border-style: solid;\n"
"	color: #808086;\n"
"	padding: 3px;\n"
"	margin-left:3px;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QTabBar::tab:selected, QTabBar::tab:last:selected, QTabBar::tab:hover {\n"
"  	border-style: solid;\n"
"	border-top-color: transparent;\n"
"	border-right-color: transparent;\n"
"	border-left-color: transparent;\n"
"	border-bottom-color: #7d15ba;\n"
"	border-bottom-width: 2px;\n"
"	border-style: solid;\n"
"	color: #FFFFFF;\n"
"	padding-left: 3px;\n"
"	padding-bottom: 2px;\n"
"	margin-left:3px;\n"
"	background-color: #1e1d23;\n"
"}\n"
"\n"
"QCheckBox {\n"
"	color: #a9b7c6;\n"
"	padding: 2px;\n"
"}\n"
"QCheckBox:disabled {\n"
"	color: #808086;\n"
"	padding: 2px;\n"
"}\n"
"\n"
"QCheckBox:hover {\n"
"	border-radius:4px;"
                        "\n"
"	border-style:solid;\n"
"	padding-left: 1px;\n"
"	padding-right: 1px;\n"
"	padding-bottom: 1px;\n"
"	padding-top: 1px;\n"
"	border-width:1px;\n"
"	border-color: rgb(87, 97, 106);\n"
"	background-color:#1e1d23;\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"\n"
"	height: 10px;\n"
"	width: 10px;\n"
"	border-style:solid;\n"
"	border-width: 1px;\n"
"	border-color: #7d15ba;\n"
"	color: #a9b7c6;\n"
"	background-color: #7d15ba;\n"
"}\n"
"QCheckBox::indicator:unchecked {\n"
"\n"
"	height: 10px;\n"
"	width: 10px;\n"
"	border-style:solid;\n"
"	border-width: 1px;\n"
"	border-color: #7d15ba;\n"
"	color: #a9b7c6;\n"
"	background-color: transparent;\n"
"}\n"
"QRadioButton {\n"
"	color: #a9b7c6;\n"
"	background-color: #1e1d23;\n"
"	padding: 1px;\n"
"}\n"
"QRadioButton::indicator:checked {\n"
"	height: 10px;\n"
"	width: 10px;\n"
"	border-style:solid;\n"
"	border-radius:5px;\n"
"	border-width: 1px;\n"
"	border-color: #7d15ba;\n"
"	color: #a9b7c6;\n"
"	background-color: #7d15ba;\n"
"}\n"
"QRadioButton::indicator:!checked {\n"
""
                        "	height: 10px;\n"
"	width: 10px;\n"
"	border-style:solid;\n"
"	border-radius:5px;\n"
"	border-width: 1px;\n"
"	border-color: #7d15ba;\n"
"	color: #a9b7c6;\n"
"	background-color: transparent;\n"
"}\n"
"QStatusBar {\n"
"	color:#027f7f;\n"
"}\n"
"QSpinBox {\n"
"	color: #a9b7c6;	\n"
"	background-color: #1e1d23;\n"
"}\n"
"QDoubleSpinBox {\n"
"	color: #a9b7c6;	\n"
"	background-color: #1e1d23;\n"
"}\n"
"QTimeEdit {\n"
"	color: #a9b7c6;	\n"
"	background-color: #1e1d23;\n"
"}\n"
"QDateTimeEdit {\n"
"	color: #a9b7c6;	\n"
"	background-color: #1e1d23;\n"
"}\n"
"QDateEdit {\n"
"	color: #a9b7c6;	\n"
"	background-color: #1e1d23;\n"
"}\n"
"QComboBox {\n"
"	color: #a9b7c6;	\n"
"	background: #1e1d23;\n"
"}\n"
"QComboBox:editable {\n"
"	background: #1e1d23;\n"
"	color: #a9b7c6;\n"
"	selection-background-color: #1e1d23;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"	color: #a9b7c6;	\n"
"	background: #1e1d23;\n"
"	selection-color: #FFFFFF;\n"
"	selection-background-color: #1e1d23;\n"
"}\n"
"QComboBox:!editable:on, QComboBox::drop-do"
                        "wn:editable:on {\n"
"	color: #a9b7c6;	\n"
"	background: #1e1d23;\n"
"}\n"
"QFontComboBox {\n"
"	color: #a9b7c6;	\n"
"	background-color: #1e1d23;\n"
"}\n"
"QToolBox {\n"
"	color: #a9b7c6;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QToolBox::tab {\n"
"	color: #a9b7c6;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QToolBox::tab:selected {\n"
"	color: #FFFFFF;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QScrollArea {\n"
"	color: #FFFFFF;\n"
"	background-color: #1e1d23;\n"
"}\n"
"QSlider::groove:horizontal {\n"
"	height: 5px;\n"
"	background: #7d15ba;\n"
"}\n"
"QSlider::groove:vertical {\n"
"	width: 5px;\n"
"	background: #7d15ba;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"	background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"	border: 1px solid #5c5c5c;\n"
"	width: 14px;\n"
"	margin: -5px 0;\n"
"	border-radius: 7px;\n"
"}\n"
"QSlider::handle:vertical {\n"
"	background: qlineargradient(x1:1, y1:1, x2:0, y2:0, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"	border: 1px solid #5c5c5c;\n"
"	height: 14"
                        "px;\n"
"	margin: 0 -5px;\n"
"	border-radius: 7px;\n"
"}\n"
"QSlider::add-page:horizontal {\n"
"    background: white;\n"
"}\n"
"QSlider::add-page:vertical {\n"
"    background: white;\n"
"}\n"
"QSlider::sub-page:horizontal {\n"
"    background: #7d15ba;\n"
"}\n"
"QSlider::sub-page:vertical {\n"
"    background: #7d15ba;\n"
"}\n"
"\n"
"QStatusBar::item{\n"
"border:none;\n"
"disblay:none;\n"
"}"));
        DarkRatCrypterUIClass->setAnimated(true);
        centralWidget = new QWidget(DarkRatCrypterUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        build = new QPushButton(centralWidget);
        build->setObjectName(QString::fromUtf8("build"));
        build->setGeometry(QRect(500, 160, 131, 51));
        build->setAutoFillBackground(false);
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
        startup->setGeometry(QRect(360, 160, 111, 17));
        startup->setStyleSheet(QString::fromUtf8(""));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 90, 91, 16));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(370, 140, 271, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        icon = new QLabel(centralWidget);
        icon->setObjectName(QString::fromUtf8("icon"));
        icon->setGeometry(QRect(370, 20, 101, 71));
        icon_path = new QLabel(centralWidget);
        icon_path->setObjectName(QString::fromUtf8("icon_path"));
        icon_path->setGeometry(QRect(360, 120, 281, 16));
        btn_icon = new QPushButton(centralWidget);
        btn_icon->setObjectName(QString::fromUtf8("btn_icon"));
        btn_icon->setGeometry(QRect(500, 60, 131, 41));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(340, 0, 20, 211));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        btn_change_output = new QPushButton(centralWidget);
        btn_change_output->setObjectName(QString::fromUtf8("btn_change_output"));
        btn_change_output->setGeometry(QRect(260, 150, 75, 23));
        outputname = new QLineEdit(centralWidget);
        outputname->setObjectName(QString::fromUtf8("outputname"));
        outputname->setGeometry(QRect(10, 150, 241, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 130, 81, 16));
        DarkRatCrypterUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DarkRatCrypterUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 656, 18));
        DarkRatCrypterUIClass->setMenuBar(menuBar);
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
        gen_mutex->setText(QApplication::translate("DarkRatCrypterUIClass", "Random", nullptr));
        gen_enckey->setText(QApplication::translate("DarkRatCrypterUIClass", "Random", nullptr));
        label->setText(QApplication::translate("DarkRatCrypterUIClass", "Pastebin URL", nullptr));
        label_2->setText(QApplication::translate("DarkRatCrypterUIClass", "Mutex", nullptr));
        startup->setText(QApplication::translate("DarkRatCrypterUIClass", "Enable Startup", nullptr));
        label_3->setText(QApplication::translate("DarkRatCrypterUIClass", "Encryption Key", nullptr));
        icon->setText(QString());
        icon_path->setText(QApplication::translate("DarkRatCrypterUIClass", "defaulticon", nullptr));
        btn_icon->setText(QApplication::translate("DarkRatCrypterUIClass", "Change Icon Path", nullptr));
        btn_change_output->setText(QApplication::translate("DarkRatCrypterUIClass", "Output Path", nullptr));
        outputname->setText(QApplication::translate("DarkRatCrypterUIClass", "spider.exe", nullptr));
        label_4->setText(QApplication::translate("DarkRatCrypterUIClass", "Output Path", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DarkRatCrypterUIClass: public Ui_DarkRatCrypterUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DARKRATCRYPTERUI_H
