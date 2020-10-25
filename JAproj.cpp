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
    ui.radioButton_cpp->setChecked(true);
}

void JAproj::on_quitButton_clicked()
{
    close();
   
}

void JAproj::createBarChart(int rDistribution[], int gDistribution[], int bDistribution[])
{
    

    QtCharts::QLineSeries* rseries = new QtCharts::QLineSeries();
    QtCharts::QLineSeries* gseries = new QtCharts::QLineSeries();
    QtCharts::QLineSeries* bseries = new QtCharts::QLineSeries();

    for (int i = 0; i < 256; i++)
    {
        *rseries << QPointF(i, rDistribution[i]);
        *gseries << QPointF(i, gDistribution[i]);
        *bseries << QPointF(i, bDistribution[i]);
    }
    rseries->setColor(Qt::red);
    gseries->setColor(Qt::green);
    bseries->setColor(Qt::blue);

    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(rseries);
    chart->addSeries(gseries);
    chart->addSeries(bseries);
    chart->createDefaultAxes();
    chart->setTitle("Histogram");

    QtCharts::QChartView* chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);
   // show();
    /*QPixmap r = QPixmap::grabWidget(redChartView);
    r.save("r.png","PNG");*/
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
       
        try 
        {
            Bitmap b(imageFilePath);
            numberOfThreads = ui.lcdNumber->intValue();
           
           

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "JAproj", "Is loaded bitmap in color?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                b.calculateHistogram();
                b.grayscale();
            }
            if (ui.radioButton_cpp->isChecked())
            {
                b.castPixelCharArrayToUnsignedCharArray();
               
                //b.calculateHistogram(); //tutaj szary bedzie
                createBarChart(b.rDistribution,b.gDistribution,b.bDistribution);
                
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
