/********************************************************************************
** Form generated from reading UI file 'HistogramWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAMWINDOW_H
#define UI_HISTOGRAMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistogramWindow
{
public:

    void setupUi(QWidget *HistogramWindow)
    {
        if (HistogramWindow->objectName().isEmpty())
            HistogramWindow->setObjectName(QString::fromUtf8("HistogramWindow"));
        HistogramWindow->resize(400, 300);

        retranslateUi(HistogramWindow);

        QMetaObject::connectSlotsByName(HistogramWindow);
    } // setupUi

    void retranslateUi(QWidget *HistogramWindow)
    {
        HistogramWindow->setWindowTitle(QCoreApplication::translate("HistogramWindow", "HistogramWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistogramWindow: public Ui_HistogramWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMWINDOW_H
