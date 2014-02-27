#include "picsym/cellmesh2d.h"
#include <QGraphicsTextItem>

namespace picsym {

void CellMesh2D::initExplosion(const size_t& max_value) {
    //const size_t diameter = width < height ? width : height;
    //const size_t radius = diameter / 2;

    const double max_x = 1.0; // scale mesh to -1:1 square
    const double min_x = -1.0;
    const double max_y = 1.0;
    const double min_y = -1.0;
    const double step_x = (max_x - min_x) / getWidth();
    const double step_y = (max_y - min_y) / getHeight();

    for (size_t y = 0; y < getHeight(); y++) {
        for (size_t x = 0; x < getWidth(); x++) {
            const double rx = min_x + x*step_x;
            const double ry = min_y + y*step_y;
            const double val = 1.0 - (rx*rx + ry*ry);
            operator ()(x, y).setNumOfParticles(val > 0 ? val*max_value : 0);
        }
    }
}

void CellMesh2D::draw(QGraphicsScene &scene) {
    size_t max_val = 0;
    for (Array<Cell>::const_iterator it = data().begin(); it != data().end(); it++)
        if (max_val < it->getNumOfParticles())
            max_val = it->getNumOfParticles();

    for (size_t y = 0; y < getHeight(); y++) {
        for (size_t x = 0; x < getWidth(); x++) {
            const size_t val = operator ()(x, y).getNumOfParticles();
            const int color = int((float(val)/float(max_val + 1))*255.0);
            scene.addRect(QRectF(x*10, y*10, 8, 8), QPen(), QBrush(QColor(color, 0, 0)));
        }
    }

    QGraphicsTextItem *item = scene.addText(QString::number(max_val));
    item->setPos(400, 10);
}

}
