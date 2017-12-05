#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mADC_stream = new ADC_stream(this);

    connect(mADC_stream, SIGNAL(samplesReceived()),
            this, SLOT(process_data()));

    mPacketInterface = new PacketInterface(this);

    connect(mPacketInterface, SIGNAL(fwVersionReceived(int,int)),
            this, SLOT(fwVersionReceived(int,int)));

    connect(ui->start_stop_capture, SIGNAL(clicked(bool)), this, SLOT(update_capture_status()));
    connect(ui->terminal_send, SIGNAL(clicked(bool)),this,SLOT(send_terminal()));

    init_waveplot();
    init_fftplot();
    cb_init();
    cb = get_bufferPointer();
    cb_enable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fwVersionReceived(int major, int minor)
{

}

void MainWindow::send_terminal(){
    QByteArray data;
    data.append((char)0);
    mPacketInterface->sendPacket(data);
}


void MainWindow::init_waveplot()
{

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->xAxis->setLabel("time (s)");
    ui->customPlot->yAxis->setLabel("Amplitude");

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssCross);
    // set axes ranges, so we see all data:

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:

    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iSelectPlottables);
    ui->customPlot->setZoomMode(true);
}

void MainWindow::init_fftplot()
{

    // create graph and assign data to it:
    ui->fft_plot->addGraph();
    ui->fft_plot->xAxis->setLabel("Frequency (Hz)");
    ui->fft_plot->yAxis->setLabel("Amplitude");
    // set axes ranges, so we see all data:

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:

    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->fft_plot->setInteractions(QCP::iRangeDrag | QCP::iSelectPlottables);
    ui->fft_plot->setZoomMode(true);
}


void MainWindow::process_data()
{

    QVector<double> ADC1;
    QVector<double> ADC2;

    int readIndex = 0;

    if (cb->size > cb->end){
        //we have wrapped

        //read from Start to End of buffer
        readIndex = cb->start;

        while(readIndex < cb->size){

            ADC1.append((cb->bp+readIndex)->voltage * 3.3/4096);
            ADC2.append((cb->bp+readIndex)->current * 3.3/4096);
            readIndex++;
        }
        readIndex=0;
        //read from start of buffer to end marker
        while(readIndex < cb->end){
            ADC1.append((cb->bp+readIndex)->voltage * 3.3/4096);
            ADC2.append((cb->bp+readIndex)->current * 3.3/4096);
            readIndex++;
        }
        if (ui->start_stop_capture->text()=="Stop"){
            update_plot(ADC1, ADC2);
        }
    }

}

void MainWindow::update_plot(QVector<double> CH1, QVector<double> CH2)
{

    //generate time vector from incoming data
    QVector<double> x(CH1.length());

    for (int i=0; i <CH1.length(); i++){
        x[i]=i;
    }

    ui->customPlot->graph(0)->setData(x, CH1);
    ui->customPlot->graph(1)->setData(x, CH2);
    ui->customPlot->yAxis->rescale();
    ui->customPlot->xAxis->rescale();
    ui->customPlot->replot();

}

void MainWindow::update_capture_status(){

    if (ui->start_stop_capture->text()=="Start"){

        ui->start_stop_capture->setText("Stop");

   }
    else{
        ui->start_stop_capture->setText("Start");
    }

}

void MainWindow::on_tab_2_destroyed()
{

}

void MainWindow::on_start_stop_capture_clicked()
{
         qDebug() << "you clicked me?";

}


void MainWindow::on_new_button_pressed()
{
         qDebug() << "MEEE";
}
