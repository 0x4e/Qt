#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //re-implemented widget event handlers
    void mouseMoveEvent(QMouseEvent * event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H