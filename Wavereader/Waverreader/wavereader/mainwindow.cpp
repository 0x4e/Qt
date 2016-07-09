#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    ui->num_samples->setValidator( new QIntValidator(1, 100000, this) );

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

void MainWindow::open_wavefile(QString file_path)
{
    int i;
    char const* fileName = file_path.toLatin1().data();

    soundfile.setFile(fileName);

    i = soundfile.getSamples();
    QString s = QString::number(i);

    ui->fileStats->setText(s);

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:

    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}

void MainWindow::update_plot()
{
    int i;
    int number_of_samples;
    QString str_num_samples = ui->num_samples->text();
    number_of_samples = str_num_samples.toInt();
    // generate some data:
    if (number_of_samples > 0)
    {
        QVector<double> x(number_of_samples),
                wave(number_of_samples);

        for (i=0; i<number_of_samples; i++) {

            wave[i] = soundfile.getCurrentSample16Bit(0);
            qDebug() << "Wave - " << wave[i];
            x[i] = i;
            soundfile.incrementSample();
        }
        ui->customPlot->graph(0)->setData(x, wave);
        ui->customPlot->graph(0)->rescaleAxes();
        ui->customPlot->replot();

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
