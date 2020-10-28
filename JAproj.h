#pragma once

#include <QtWidgets/QMainWindow>
#include<QtCharts/qchartview.h>
#include<QtCharts/qbarseries.h>
#include<QtCharts/qbarset.h>
#include<QtCharts/qlineseries.h>
#include<QtCharts/qlegend.h>
#include<QtCharts/qbarcategoryaxis.h>
#include<QtCharts/qvalueaxis.h>
#include <QPixmap>
#include <QLabel>
#include "ui_JAproj.h"
#include "bitmap.h"
#include "timer.h"
#include<vector>
#include<thread>

class JAproj : public QMainWindow
{
    Q_OBJECT
    
public:
    JAproj(QWidget *parent = Q_NULLPTR);
    QtCharts::QChartView* createLineChart(int rDistribution[], int gDistribution[], int bDistribution[], std::string histogramFilePath, bool beforeOrAfterAlgorithm);
    void displayHistograms(QtCharts::QChartView* beforeAlgorithmHistogram, QtCharts::QChartView* afterAlgorithmHistogram);
    
private slots:
    void on_quitButton_clicked();
    void on_openButton_clicked();
    void on_startAlgorithmButton_clicked();
private:
    Ui::JAprojClass ui;
    
    
};
