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
    QString filePath = QFileDialog::getOpenFileName(this,tr("Image chooser")," " ,tr("BMP Files (*.bmp)"));   
    imageFilePath = filePath.toLocal8Bit().constData();
    QMessageBox::information(this, tr("file name"), "Selected file path: "+filePath);
}

void JAproj::on_startAlgorithmButton_clicked()
{

    if (ui.radioButton_cpp->isChecked() || ui.radioButton_asm->isChecked())
    {
       // Bitmap background("background.BMP");
        try 
        {
            Bitmap b(imageFilePath);
            Bitmap background("background.BMP");
            numberOfThreads = ui.lcdNumber->intValue();
            Histogram h(background);
           

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "JAproj", "Is loaded bitmap in color?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                b.grayscale();
            }
            if (ui.radioButton_cpp->isChecked())
            {
                h.calculateHistogram(b);
               h.saveHistogram(imageFilePath);
                b.castPixelCharArrayToUnsignedCharArray();
                b.makeMagic();
               b.saveToFile(imageFilePath);
            }
            else if (ui.radioButton_asm->isChecked())
            {
            }
        }
        catch (...)
        {
            QMessageBox::information(this, tr("ERROR"), "Please select file to be opened.");
        }
        
    }
    else
    {
        QMessageBox::information(this, tr("ERROR"), "Please choose dll.");
    }
   
    
    
}
