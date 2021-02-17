#include "JAproj.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qprogressbar.h>
#include <qbuttongroup.h>
#include <vector>
#include <Windows.h>
#include<time.h>
#include<cstdint>

typedef void(__cdecl* pPrewittFilter)(char* inputArray,   char* outputArray, int width, int start_height, int stop_height);
typedef uint32_t(__cdecl* pPrewittFilterASM)(char* inputArray,  char* outputArray,int width, int start_height,int stop_height);

JAproj::JAproj(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lcdNumber->display(1); 
    ui.radioButton_cpp->setChecked(true);
    ui.cppTimeLabel->setText("N/A");
    ui.asmAlgorithmTime->setText("N/A");
    ui.horizontalSlider->setValue(std::thread::hardware_concurrency());
  
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
    Bitmap b;
    try
    {
        bool load = b.loadBitmap(imageFilePath);
        if (!load)
        {
            QMessageBox::information(this, tr("ERROR"), "File is too big. Maximum file size is 1GB.");
            return;
        }
    }
    catch (...)
    {
        QMessageBox::information(this, tr("ERROR"), "Please select file to be opened.");
        return;
    }
    b.castPixelCharArrayToUnsignedCharArray();
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
    QtCharts::QChartView* beforeHistogram = nullptr;
    QtCharts::QChartView* afterHistogram = nullptr;
    std::vector<std::thread> threadVector;

    numberOfThreads = ui.lcdNumber->intValue();
    int total_rows = b.getHeight();

    int rows = double(total_rows % numberOfThreads);
    int rows_per_thread = floor(total_rows / numberOfThreads);
    beforeHistogram = createLineChart(b.getRDistribution(), b.getGDistribution(), b.getBDistribution(), imageFilePath, true);

    int arraySize = b.getFilesize() - b.getOffsetToPixels();
    char* temp = new  char[arraySize];

     bool ifCppDllChosen = true;
    if (ui.radioButton_cpp->isChecked())
    {      
       
        HMODULE hModule;
        hModule = LoadLibrary(TEXT("PrewittCpp.dll"));
        pPrewittFilter prewittFilter = (pPrewittFilter)GetProcAddress(hModule, "prewittFilter");

        if (hModule == NULL)
        {
            QMessageBox::information(this, tr("ERROR"), "DLL C++ library was not found.");
            return;
        }
        Timer cppAlgoTimer;
            cppAlgoTimer.start();
            for (int i = numberOfThreads; i > 0; i--)
            {

                int start_row = rows_per_thread * (numberOfThreads - i);

                if (i == 1)
                {
                    int end_row = rows_per_thread * (numberOfThreads - i + 1) + rows;
                    std::thread fred(prewittFilter, b.getPixels(), temp, b.getWidth(), start_row, end_row);
                    threadVector.push_back(std::move(fred));
                }
                else
                {
                    int end_row = rows_per_thread * (numberOfThreads - i + 1);
                    std::thread fred(prewittFilter, b.getPixels(), temp, b.getWidth(), start_row, end_row + 2);
                    threadVector.push_back(std::move(fred));
                }

            }

            for (std::thread& temp : threadVector)
            {
                temp.join();
            }
            cppAlgoTimer.stop();
            int cppAlgorithmTime = cppAlgoTimer.getTime();
            ui.cppTimeLabel->setText(QString::number(cppAlgorithmTime) + "ms");
   
        FreeLibrary(hModule);  
    }
    else if(ui.radioButton_asm->isChecked())
    {
        HMODULE hModule;
        hModule = LoadLibrary(TEXT("PrewittASM.dll"));
        pPrewittFilterASM prewittFilter = (pPrewittFilterASM)GetProcAddress(hModule, "prewittFilter");

        if (hModule == NULL)
        {
            QMessageBox::information(this, tr("ERROR"), "DLL ASM library was not found.");
            return;
        }
            Timer asmAlgoTimer;

            asmAlgoTimer.start();
            for (int i = numberOfThreads; i > 0; i--)
            {

                int start_row = rows_per_thread * (numberOfThreads - i);

                if (i == 1)
                {
                    int end_row = rows_per_thread * (numberOfThreads - i + 1) + rows;
                    std::thread fred(prewittFilter, b.getPixels(), temp, b.getWidth() - 2, start_row, end_row - 2);
                    threadVector.push_back(std::move(fred));
                }
                else
                {
                    int end_row = rows_per_thread * (numberOfThreads - i + 1);
                    std::thread fred(prewittFilter, b.getPixels(), temp, b.getWidth() - 2, start_row, end_row);
                    threadVector.push_back(std::move(fred));
                }

            }

            for (std::thread& temp : threadVector)
            {
                temp.join();
            }
            asmAlgoTimer.stop();
            int cppAlgorithmTime = asmAlgoTimer.getTime();
             ui.asmAlgorithmTime->setText(QString::number(cppAlgorithmTime) + "ms");
        FreeLibrary(hModule);
        ifCppDllChosen = false;
    }
    b.setPixels((char*)temp);
    b.calculateHistogram();
    afterHistogram = createLineChart(b.getRDistribution(), b.getGDistribution(), b.getBDistribution(), imageFilePath, false);
    b.saveToFile(imageFilePath,ifCppDllChosen);
    displayHistograms(beforeHistogram, afterHistogram);
    
}
