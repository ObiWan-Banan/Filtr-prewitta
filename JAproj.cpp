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
    QString filePath = QFileDialog::getOpenFileName(this,tr("Image chooser")," " ,tr("Image Files (*.png *.jpg *.bmp)"));   
    imageFilePath = filePath.toLocal8Bit().constData();
    QMessageBox::information(this, tr("file name"), "Selected file path: "+filePath);
}

void JAproj::on_startAlgorithmButton_clicked()
{

    bitmap b(imageFilePath);
    if (ui.radioButton_cpp->isChecked())
    {
       
            
    }
    else if (ui.radioButton_asm->isChecked())
    {

    }  
    else
    {
        QMessageBox::information(this, tr("ERROR"), "Please choose dll.");
    }
    
}
