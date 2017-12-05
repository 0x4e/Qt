#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ADC_stream.h"
#include "circular_buffer.h"
#include "packetinterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:

    Ui::MainWindow *ui;
    ADC_stream *mADC_stream;
    PacketInterface *mPacketInterface;
    void init_waveplot();
    void init_fftplot();
    CircularBuffer *cb;
    void update_plot(QVector<double> CH1, QVector<double> CH2);


private slots:

    void process_data();
    void update_capture_status();
    void fwVersionReceived(int major, int minor);
    void on_tab_2_destroyed();
    void send_terminal();

    void on_start_stop_capture_clicked();

    void on_new_button_pressed();
};

#endif // MAINWINDOW_H
