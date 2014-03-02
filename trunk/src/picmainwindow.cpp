#include "picmainwindow.h"
#include "ui_picmainwindow.h"
//#include "picsym/base/hilbert.h"
//#include "picsym/slicer.h"

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
    const size_t mesh_size = ui->sizeBox->value();
    const size_t num_of_nodes = ui->nodesBox->value();

    scene.clear();

    mesh.setDimensions(mesh_size, mesh_size);
    mesh.initIds();
    mesh.initExplosion(100);
    mesh.draw(scene);

    machine.start(num_of_nodes, mesh);

    /*size_t prev_x = 0, prev_y = 0;

    QPainterPath path;
    path.moveTo(prev_x*scale, prev_y*scale);

    for (size_t dist = 1; dist < mesh_size*mesh_size; dist++) {
        size_t x, y;
        picsym::Hilbert::distanceToCoord(dist, mesh_size, x, y);
        path.lineTo(x*scale, y*scale);
        prev_x = x;
        prev_y = y;
    }

    scene.clear();
    scene.addPath(path);*/
}

void PICMainWindow::on_sizeBox_valueChanged(int arg1)
{
}

void PICMainWindow::on_nodesBox_valueChanged(int arg1)
{

}

void PICMainWindow::on_stopButton_clicked()
{
    machine.stop();
}
