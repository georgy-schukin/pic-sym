#ifndef PICMAINWINDOW_H
#define PICMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
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
    void on_sizeBox_valueChanged(int arg1);
    void on_nodesBox_valueChanged(int arg1);

    void on_stopButton_clicked();

private:
    Ui::PICMainWindow *ui;    
    QGraphicsScene scene;

    picsym::CellMesh2D mesh;
    picsym::ParallelMachine machine;
};

#endif // PICMAINWINDOW_H
