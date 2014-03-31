#include "picmainwindow.h"
#include "ui_picmainwindow.h"
#include "picsym/base/globalenv.h"

PICMainWindow::PICMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PICMainWindow)
{
    ui->setupUi(this);    

    ui->graphicsView->setScene(&cells_scene);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    ui->graphicsView_2->setScene(&load_scene);
    ui->graphicsView_2->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    ui->coeffValueLabel->setText(QString::number(ui->balanceCoeffSlider->value()));
}

PICMainWindow::~PICMainWindow()
{
    delete ui;
}

void PICMainWindow::on_startButton_clicked()
{    
    const size_t mesh_size = ui->sizeBox->value();
    const size_t num_of_nodes = ui->nodesBox->value();    

    mesh = picsym::CellMesh2D(mesh_size, mesh_size, picsym::Rect2D<picsym::Real>(-1, 1, 1, -1));
    mesh.generateExplosion(100);

    picsym::GlobalEnvironment& env = picsym::GlobalEnvironment::get();
        env.setTotalNumOfCells(mesh.getNumOfCells());
        env.setTotalNumOfParticles(mesh.getNumOfParticles());
        env.setMeshSize(mesh.getWidth());
        env.setBalanceCoeff(double(ui->balanceCoeffSlider->value())/(ui->balanceCoeffSlider->maximum() - ui->balanceCoeffSlider->minimum()));

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
    cells_scene.clear();
    load_scene.clear();

    machine.drawCells(cells_scene);
    machine.drawLoad(load_scene);
}

void PICMainWindow::on_balanceCoeffSlider_valueChanged(int value)
{
    const double coeff = double(value)/(ui->balanceCoeffSlider->maximum() - ui->balanceCoeffSlider->minimum());
    ui->coeffValueLabel->setText(QString::number(value));
    picsym::GlobalEnvironment::get().setBalanceCoeff(coeff);
}
