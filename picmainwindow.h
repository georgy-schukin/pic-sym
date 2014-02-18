#ifndef PICMAINWINDOW_H
#define PICMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PICMainWindow;
}

class PICMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PICMainWindow(QWidget *parent = 0);
    ~PICMainWindow();
    
private:
    Ui::PICMainWindow *ui;
};

#endif // PICMAINWINDOW_H
