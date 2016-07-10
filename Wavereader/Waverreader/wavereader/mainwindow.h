#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "soundfile.h"
#include <stdlib.h>

#ifndef OLDCPP
   #include <iostream>
   using namespace std;
#else
   #include <iostream.h>
#endif



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
    float * get_waveform(SoundFileRead &soundfile);
    void open_wavefile(QString file_path);
    SoundFileRead soundfile;
    void init_waveplot();
    void init_fftplot();

private slots:
    void open_file();
    void exit();
    void update_plot();



};

#endif // MAINWINDOW_H
