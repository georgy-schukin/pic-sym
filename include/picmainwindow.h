#ifndef PICMAINWINDOW_H
#define PICMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "picsym/mesh2d.h"
#include "picsym/machine.h"
#include "picviz.h"
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

private:
    Ui::PICMainWindow *ui;    
    QGraphicsScene scene;
    picsym::Mesh2D mesh;  
    picsym::Machine machine;
    //PICVisualizer visualizer;
};

#endif // PICMAINWINDOW_H
