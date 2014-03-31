#pragma once

#ifndef Q_MOC_RUN
#include <boost/scoped_ptr.hpp>
#endif

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "picsym/cellmesh2d.h"
#include "picsym/parallelmachine.h"
#include <vector>

namespace Ui {
class PICMainWindow;
}

class PICMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PICMainWindow(QWidget *parent = 0);
    ~PICMainWindow();
    
private slots:
    void on_startButton_clicked();    
    void on_stopButton_clicked();

    void on_sizeBox_valueChanged(int arg1);
    void on_nodesBox_valueChanged(int arg1);    
    void on_balanceCoeffSlider_valueChanged(int value);

    void draw();          

private:
    Ui::PICMainWindow *ui;    
    QGraphicsScene cells_scene, load_scene;

    picsym::CellMesh2D mesh;
    picsym::ParallelMachine machine;

    boost::scoped_ptr<QTimer> timer;
};

