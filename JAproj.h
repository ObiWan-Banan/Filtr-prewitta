#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_JAproj.h"


class JAproj : public QMainWindow
{
    Q_OBJECT

public:
    JAproj(QWidget *parent = Q_NULLPTR);
    
private slots:
    void on_quitButton_clicked();
    void on_openButton_clicked();
    void on_startAlgorithmButton_clicked();
private:
    Ui::JAprojClass ui;
};
