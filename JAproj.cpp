#include "JAproj.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qprogressbar.h>
#include <qbuttongroup.h>
#include <vector>



JAproj::JAproj(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lcdNumber->display(1);
    
    
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

    if (ui.radioButton_cpp->isChecked() || ui.radioButton_asm->isChecked())
    {
        try {
            Bitmap b(imageFilePath);
            b.grayscale();
            b.makeMagic();
            b.saveToFile(imageFilePath);
        }
        catch (...)
        {
            QMessageBox::information(this, tr("ERROR"), "Please select file to be opened.");
        }
        numberOfThreads = ui.lcdNumber->intValue();
        if (ui.radioButton_cpp->isChecked())
        {

        }
        else if(ui.radioButton_asm->isChecked())
        {
        }
    }
    else
    {
        QMessageBox::information(this, tr("ERROR"), "Please choose dll.");
    }
   
    
    
}
