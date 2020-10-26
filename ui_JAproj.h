/********************************************************************************
** Form generated from reading UI file 'JAproj.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JAPROJ_H
#define UI_JAPROJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JAprojClass
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *openButton;
    QPushButton *startAlgorithmButton;
    QPushButton *quitButton;
    QTextBrowser *textBrowser;
    QSlider *horizontalSlider;
    QTextBrowser *textBrowser_2;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_cpp;
    QRadioButton *radioButton_asm;
    QLCDNumber *lcdNumber;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *JAprojClass)
    {
        if (JAprojClass->objectName().isEmpty())
            JAprojClass->setObjectName(QString::fromUtf8("JAprojClass"));
        JAprojClass->resize(376, 285);
        centralWidget = new QWidget(JAprojClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 170, 361, 81));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        openButton = new QPushButton(horizontalLayoutWidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));

        horizontalLayout->addWidget(openButton);

        startAlgorithmButton = new QPushButton(horizontalLayoutWidget);
        startAlgorithmButton->setObjectName(QString::fromUtf8("startAlgorithmButton"));

        horizontalLayout->addWidget(startAlgorithmButton);

        quitButton = new QPushButton(horizontalLayoutWidget);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));

        horizontalLayout->addWidget(quitButton);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(130, 30, 241, 51));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 130, 351, 22));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(64);
        horizontalSlider->setOrientation(Qt::Horizontal);
        textBrowser_2 = new QTextBrowser(centralWidget);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(10, 90, 101, 31));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 120, 80));
        radioButton_cpp = new QRadioButton(groupBox_2);
        radioButton_cpp->setObjectName(QString::fromUtf8("radioButton_cpp"));
        radioButton_cpp->setGeometry(QRect(10, 20, 82, 17));
        radioButton_asm = new QRadioButton(groupBox_2);
        radioButton_asm->setObjectName(QString::fromUtf8("radioButton_asm"));
        radioButton_asm->setGeometry(QRect(10, 50, 82, 17));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(300, 90, 71, 31));
        JAprojClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(JAprojClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        JAprojClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(JAprojClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        JAprojClass->setStatusBar(statusBar);

        retranslateUi(JAprojClass);
        QObject::connect(quitButton, SIGNAL(clicked()), JAprojClass, SLOT(on_quitButton_clicked()));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));

        QMetaObject::connectSlotsByName(JAprojClass);
    } // setupUi

    void retranslateUi(QMainWindow *JAprojClass)
    {
        JAprojClass->setWindowTitle(QCoreApplication::translate("JAprojClass", "JAproj", nullptr));
        openButton->setText(QCoreApplication::translate("JAprojClass", "Open File", nullptr));
        startAlgorithmButton->setText(QCoreApplication::translate("JAprojClass", "Start algorithm", nullptr));
        quitButton->setText(QCoreApplication::translate("JAprojClass", "Quit", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("JAprojClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Filtr Prewitt'a z histogramem</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">autor: Rafa\305\202 \305\232widerski</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("JAprojClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Thread slider:</span></p></body></html>", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("JAprojClass", "DLL", nullptr));
        radioButton_cpp->setText(QCoreApplication::translate("JAprojClass", "C++", nullptr));
        radioButton_asm->setText(QCoreApplication::translate("JAprojClass", "ASM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JAprojClass: public Ui_JAprojClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JAPROJ_H
