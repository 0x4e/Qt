#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kiss_fft.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open_file()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));
    connect(ui->nextFrame, SIGNAL(clicked(bool)), this, SLOT(update_plot()));


    //setup sample size input box
    ui->num_samples->setValidator( new QIntValidator(1, 100000, this) );
    ui->num_samples->setText("1024");

    init_waveplot();
    init_fftplot();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::open_file()
{
    QString file_path = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/home",
                "All files (*.*);;Text File (*.txt)"
                );

    open_wavefile(file_path);
}

// 31 , 9,

void MainWindow::init_waveplot()
{

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setLabel("time (s)");
    ui->customPlot->yAxis->setLabel("Amplitude");
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


void MainWindow::open_wavefile(QString file_path)
{
    char const* fileName = file_path.toLatin1().data();

    soundfile.setFile(fileName);

    ui->fileStats->setText(file_path);
    QString print_string = QString("%1 %2").arg("Bits per sample = ",QString::number(soundfile.getBitsPerSample()));
    ui->fileStats->append(print_string);
    print_string = QString("%1 %2").arg("Channels = ",QString::number(soundfile.getChannels()));
    ui->fileStats->append(print_string);
    print_string = QString("%1 %2").arg("Sampling rate = ",QString::number(soundfile.getSrate()));
    ui->fileStats->append(print_string);
    print_string = QString("%1 %2").arg("Samples = ",QString::number(soundfile.getSamples()));
    ui->fileStats->append(print_string);
    print_string = QString("%1 %2").arg("Data bytes = ",QString::number(soundfile.getDataByteSize()));
    ui->fileStats->append(print_string);
    print_string = QString("%1 %2").arg("Data Offset = ",QString::number(soundfile.getDataByteOffset()));
    ui->fileStats->append(print_string);
    print_string = QString("%1 %2").arg("Duration = ",QString::number(soundfile.getSamples()/soundfile.getSrate()));
    ui->fileStats->append(print_string);
    print_string = QString("%1 %2").arg("Byte Rate = ",QString::number(soundfile.getBitsPerSample()/8.0 * soundfile.getSrate() * soundfile.getChannels()));
    ui->fileStats->append(print_string);


}

void MainWindow::update_plot()
{
    int i;
    int number_of_samples;
    float rescale;
    QString str_num_samples = ui->num_samples->text();
    number_of_samples = str_num_samples.toInt();


    if (number_of_samples > 0)
    {
        //Calculate rescale factor
        rescale = 1.0 / pow(2,(soundfile.getBitsPerSample()-1));


        //Grab data
        QVector<double> x(number_of_samples),
                wave(number_of_samples);


        for (i=0; i < number_of_samples; i++) {

            wave[i] = soundfile.getCurrentSample16Bit(0) * rescale;

            x[i] = i *1.0/soundfile.getSrate();
            soundfile.incrementSample();
        }

        //plot waveform
        ui->customPlot->graph(0)->setData(x, wave);
        ui->customPlot->graph(0)->rescaleAxes();
        ui->customPlot->replot();

        //plot fft
        kiss_fft_cpx in[number_of_samples], out[number_of_samples];
        kiss_fft_cfg cfg;

        for (i = 0; i < number_of_samples; i++)
        {
            in[i].r = wave[i];
            in[i].i = 0;
        }


        if ((cfg = kiss_fft_alloc(number_of_samples, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
        {
          size_t i;

          kiss_fft(cfg, in, out);
          free(cfg);

          for (i = 0; i < number_of_samples; i++)
            printf(" in[%2zu] = %+f , %+f    "
                   "out[%2zu] = %+f , %+f\n",
                   i, in[i].r, in[i].i,
                   i, out[i].r, out[i].i);
        }
        else
        {
          printf("not enough memory?\n");
          //exit(-1);
        }

        QVector<double> fftx(number_of_samples/2),
                ffty(number_of_samples/2);


        for (i = 0; i < number_of_samples/2; i++)
        {
            fftx[i] = i * (1.0 *soundfile.getSrate()/number_of_samples);
            //ffty[i] = 20* log((sqrt((out[i].r *out[i].r) + (out[i].i *out[i].i)))/number_of_samples) ;
            //ffty[i] = (sqrt((out[i].r *out[i].r) + (out[i].i *out[i].i)))/number_of_samples ;
            //ffty[i] = (sqrt((out[i].r *out[i].r) + (out[i].i *out[i].i)))/(number_of_samples/2) ;

            //one test file very close, another off by 100. Scaling is not correct method. Need to learn correct way.
            ffty[i] = 20* log((sqrt((out[i].r *out[i].r) + (out[i].i *out[i].i)))/(number_of_samples/2.0));

        }

        //plot waveform
        ui->fft_plot->graph(0)->setData(fftx, ffty);
        ui->fft_plot->graph(0)->rescaleAxes();
        ui->fft_plot->replot();

        //update Stats
        ui->fileStats->append(QString::number(soundfile.getCurrentSampleIndex()));
        ui->fileStats->ensureCursorVisible();
        QTextCursor tCursor = ui->fileStats->textCursor();
        tCursor.movePosition(QTextCursor::End);
        ui->fileStats->setTextCursor(tCursor);

    }

}



void MainWindow::exit()
{
    QApplication::quit();
}
