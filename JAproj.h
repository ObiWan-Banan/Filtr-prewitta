#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_JAproj.h"

class JAproj : public QMainWindow
{
    Q_OBJECT

public:
    JAproj(QWidget *parent = Q_NULLPTR);

private:
    Ui::JAprojClass ui;
};
