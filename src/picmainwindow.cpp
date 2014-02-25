#include "picmainwindow.h"
#include "ui_picmainwindow.h"
#include "picsym/hilbert.h"

PICMainWindow::PICMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PICMainWindow)
{
    ui->setupUi(this);

    scene.setSceneRect(0, 0, 100, 100);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

PICMainWindow::~PICMainWindow()
{
    delete ui;
}

void PICMainWindow::on_startButton_clicked()
{    
    const size_t mesh_size = 32;
    const size_t scale = 10;    

    size_t prev_x = 0, prev_y = 0;

    QPainterPath path;
    path.moveTo(prev_x*scale, prev_y*scale);

    for (size_t dist = 1; dist < mesh_size*mesh_size; dist++) {
        size_t x, y;
        picsym::Hilbert::distanceToCoord(dist, mesh_size, x, y);
        path.lineTo(x*scale, y*scale);
        prev_x = x;
        prev_y = y;
    }

    scene.addPath(path);

    //scene.addRect(0, 0, ui->graphicsView->geometry().width() - 10, ui->graphicsView->geometry().height() - 10);
    //visualizer.draw();
}

void PICMainWindow::on_widthBox_valueChanged(int arg1)
{
  //  width = arg1;
}

void PICMainWindow::on_heightBox_valueChanged(int arg1)
{

}
