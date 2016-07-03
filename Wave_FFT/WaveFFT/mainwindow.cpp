#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QElapsedTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mTimer = new QTimer(this);
    mTimer->setInterval(TIMERINTERVAL);
    mTimer->start();

    connect(mTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::timerSlot()
{
    static QVector<double> filter;
    QElapsedTimer timer;
    timer.start();

    filter.append(1.9);
    filter.append(10.1);

    // Plot filter
    QVector<double> filterIndex;
    for(int i = 0;i < filter.size();i++) {
        filterIndex.append((double)i);
    }
    ui->filterPlot->graph(0)->setData(filterIndex, filter);
    ui->filterPlot->graph(0)->setName("Filter");
    ui->filterPlot->graph(0)->setLineStyle(QCPGraph::lsLine);


    ui->filterPlot->legend->setVisible(true);
    //ui->filterPlot->legend->setFont(legendFont);
    ui->filterPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
    ui->filterPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    ui->filterPlot->xAxis->setLabel("Index");
    ui->filterPlot->yAxis->setLabel("Value");

    ui->filterPlot->rescaleAxes();
    ui->filterPlot->replot();


    //qDebug("elapsed time = %d",(start-end));
    //qDebug() << timer.elapsed();
}
