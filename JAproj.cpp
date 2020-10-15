#include "JAproj.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qprogressbar.h>
#include <qbuttongroup.h>



JAproj::JAproj(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);   
}

void JAproj::on_quitButton_clicked()
{
    close();
}

void JAproj::on_openButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Image chooser")," " ,tr("Image Files (*.png *.jpg *.bmp)"));
    QMessageBox::information(this, tr("file name"), "Selected file path: "+filename);
}

void JAproj::on_startAlgorithmButton_clicked()
{
    if (ui.checkBox_cpp->isChecked())
    {
        
    }
    else if (ui.checkBox_asm->isChecked())
    {
        
    }
    else if (ui.checkBox_asm->isChecked() && ui.checkBox_cpp->isChecked())
    {
        QMessageBox::information(this, tr("ERROR"), "Two dll are chosen, please select only one.");
    }
    else
    {
        QMessageBox::information(this, tr("ERROR"), "Please choose dll.");
    }
    
}
