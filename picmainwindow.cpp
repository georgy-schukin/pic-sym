#include "picmainwindow.h"
#include "ui_picmainwindow.h"

PICMainWindow::PICMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PICMainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
}

PICMainWindow::~PICMainWindow()
{
    delete ui;
}

void PICMainWindow::on_startButton_clicked()
{
    scene.addRect(10, 10, 20, 20);
}

void PICMainWindow::on_widthBox_valueChanged(int arg1)
{

}

void PICMainWindow::on_heightBox_valueChanged(int arg1)
{

}
