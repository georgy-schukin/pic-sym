#include "picmainwindow.h"
#include "ui_picmainwindow.h"

PICMainWindow::PICMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PICMainWindow)
{
    ui->setupUi(this);
}

PICMainWindow::~PICMainWindow()
{
    delete ui;
}
