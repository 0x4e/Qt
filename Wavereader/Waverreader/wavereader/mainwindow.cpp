#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open_file()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));


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


}


void MainWindow::exit()
{

}
