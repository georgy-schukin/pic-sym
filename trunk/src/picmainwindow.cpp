#include "picmainwindow.h"
#include "ui_picmainwindow.h"
//#include "picsym/base/hilbert.h"
//#include "picsym/slicer.h"

PICMainWindow::PICMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PICMainWindow)
{
    ui->setupUi(this);    

    ui->graphicsView->setScene(&mesh_scene);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    ui->graphicsView_2->setScene(&machine_scene);
    ui->graphicsView_2->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

PICMainWindow::~PICMainWindow()
{
    delete ui;
}

void PICMainWindow::on_startButton_clicked()
{    
    const size_t mesh_size = ui->sizeBox->value();
    const size_t num_of_nodes = ui->nodesBox->value();

    mesh_scene.clear();
    machine_scene.clear();

    mesh.setDimensions(mesh_size, mesh_size);
    mesh.initIds();
    mesh.initExplosion(100);    

    machine.start(num_of_nodes, mesh);        

    timer.reset(new QTimer(this));
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(draw()));
    timer->start(500);

    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void PICMainWindow::on_stopButton_clicked()
{
    machine.stop();
    if (timer.get()) {
        timer->stop();
    }

    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

void PICMainWindow::on_sizeBox_valueChanged(int arg1)
{
}

void PICMainWindow::on_nodesBox_valueChanged(int arg1)
{

}

void PICMainWindow::draw() {
    mesh_scene.clear();
    machine_scene.clear();

    mesh.draw(mesh_scene);
    machine.draw(machine_scene);
}
