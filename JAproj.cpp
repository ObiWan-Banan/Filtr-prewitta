#include "JAproj.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qprogressbar.h>
#include <qbuttongroup.h>
#include <vector>
#include <Windows.h>


typedef int(__cdecl* pPrewittFilter)(char* inputArray,  unsigned char* outputArray, int width, int start_height, int stop_height);

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

QtCharts::QChartView* JAproj::createLineChart(int rDistribution[],int gDistribution[], int bDistribution[], std::string histogramFilePath, bool beforeOrAfterAlgorithm)
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
    rseries->setColor(QColorConstants::Red);
    gseries->setColor(QColorConstants::Green);
    bseries->setColor(QColorConstants::Blue);

    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(rseries);
    chart->addSeries(gseries);
    chart->addSeries(bseries);
    chart->createDefaultAxes();
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    if (beforeOrAfterAlgorithm)
    {
        chart->setTitle("Before algorithm histogram");
    }
    else
    {
        chart->setTitle("After algorithm histogram");
    }
   

    QtCharts::QChartView* chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
 
    return chartView;
 

}

void JAproj::displayHistograms(QtCharts::QChartView* beforeAlgorithmHistogram, QtCharts::QChartView* afterAlgorithmHistogram)
{
    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(beforeAlgorithmHistogram);
    lay->addWidget(afterAlgorithmHistogram);

    QWidget* w = new QWidget();
    w->setLayout(lay);
    w->resize(600, 500);
    w->show();
    
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
        QtCharts::QChartView* beforeHistogram = nullptr;
        QtCharts::QChartView* afterHistogram = nullptr;
        std::vector<std::thread> threadVector;
        try 
        {
            Bitmap b(imageFilePath);
            numberOfThreads = ui.lcdNumber->intValue();
            int total_rows = b.getHeight();
            /*int rows = double(total_rows % 4);
            int rows_per_thread = floor(total_rows / 4);*/
            int rows = double(total_rows % numberOfThreads);
            int rows_per_thread = floor(total_rows / numberOfThreads);

            /*int row_t1 = rows_per_thread;
            int row_t2 = rows_per_thread * 2 + rows;
            int row_t3 = rows_per_thread * 3;
            int row_t4 = rows_per_thread * 4 + rows;*/
           

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "JAproj", "Is loaded bitmap in color?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                b.calculateHistogram();
                b.grayscale();
            }
            else
            {
                b.calculateHistogram();
            }
            if (ui.radioButton_cpp->isChecked())
            {
                HMODULE hModule;
                hModule = LoadLibrary(TEXT("PrewittCpp.dll"));
                pPrewittFilter prewittFilter = (pPrewittFilter)GetProcAddress(hModule, "prewittFilter");

                b.castPixelCharArrayToUnsignedCharArray();
                //beforeHistogram=createLineChart(b.rDistribution, b.gDistribution, b.bDistribution, imageFilePath, true);
                beforeHistogram=createLineChart(b.getRDistribution(), b.getGDistribution(), b.getBDistribution(), imageFilePath, true);
                //prewittFilter(b.pixel_data, b.width, b.height, (b.filesize - b.offset_to_pixel_data));
                int arraySize = b.getFilesize() - b.getOffsetToPixels();
                unsigned char* temp = new unsigned char[arraySize];
               


                /*std::thread t1(prewittFilter, b.getPixels(), temp, b.getWidth(), 0, row_t1 + 2);
                std::thread t2(prewittFilter, b.getPixels(), temp, b.getWidth(), row_t1, row_t2 + 2);
                std::thread t3(prewittFilter, b.getPixels(), temp, b.getWidth(), row_t2, row_t3 + 2);
                std::thread t4(prewittFilter, b.getPixels(), temp, b.getWidth(), row_t3, row_t4);
                t1.join();
                t2.join();
                t3.join();
                t4.join();*/
                b.setPixels((char*)temp);
               // b.makeMagic();
                
                FreeLibrary(hModule);
                b.calculateHistogram();
               // afterHistogram=createLineChart(b.rDistribution, b.gDistribution, b.bDistribution, imageFilePath, false);
                afterHistogram=createLineChart(b.getRDistribution(), b.getGDistribution(), b.getBDistribution(), imageFilePath, false);
               b.saveToFile(imageFilePath);
            }
            else if (ui.radioButton_asm->isChecked())
            {
            }
            displayHistograms(beforeHistogram, afterHistogram);
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
