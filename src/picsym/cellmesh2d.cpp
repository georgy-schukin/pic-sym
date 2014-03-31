#include "picsym/cellmesh2d.h"
#include "picsym/base/hilbert.h"
#include <cmath>
#include <QGraphicsTextItem>

namespace picsym {

void CellMesh2D::generateExplosion(const size_t &max_value) {
    for (size_t x = 0; x < getWidth(); x++) {
        for (size_t y = 0; y < getHeight(); y++) {                        
            operator ()(x, y).setParticles(generateExplosionParticles(x, y, max_value));
        }
    }
}

std::list<Particle> CellMesh2D::generateExplosionParticles(const size_t &x, const size_t &y, const size_t &max_value) {
    std::list<Particle> particles;
    const LoadType step_x = bounds.width() / getWidth();
    const LoadType step_y = bounds.height() / getHeight();
    const LoadType rx = bounds.getLeft() + x*step_x;
    const LoadType ry = bounds.getBottom() + y*step_y;
    const LoadType cx = bounds.getLeft() + bounds.width() / 2.0;
    const LoadType cy = bounds.getBottom() + bounds.height() / 2.0;

    const LoadType val = 0.5 - (rx*rx + ry*ry);
    const size_t num_of_particles = val > 0 ? val*max_value : 0;
    for (size_t n = 0; n < num_of_particles; n++) {
        const LoadType px = rx + step_x*LoadType(rand() % 1000)/1000.0;
        const LoadType py = ry + step_y*LoadType(rand() % 1000)/1000.0;
        particles.push_back(Particle(Coord2D<Real>(px, py), Coord2D<Real>(px - cx, py - cy)));
    }

    return particles;
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
}

void CellMesh2D::init() {
    const LoadType step_x = bounds.width() / getWidth();
    const LoadType step_y = bounds.height() / getHeight();
    for (size_t x = 0; x < getWidth(); x++) {
        for (size_t y = 0; y < getHeight(); y++) {
            Cell& cell = operator ()(x, y);
            const LoadType rx = bounds.getLeft() + x*step_x;
            const LoadType ry = bounds.getBottom() + y*step_y;
            cell.setBounds(Rect2D<Real>(rx, rx + step_x, ry, ry + step_y));
            cell.setId(Hilbert::coordToDistance(x, y, getWidth()));
        }
    }
}

CellRange CellMesh2D::getRange(const size_t &start, const size_t &end) const {
    CellRange range;
    for (size_t dist = start; dist < end; dist++) {
        range.add(this->operator ()(Hilbert::distanceToCoord(dist, getWidth())));
    }
    return range;
}

size_t CellMesh2D::getNumOfParticles() const {
    size_t total_num_of_particles = 0;
    for (Array<Cell>::const_iterator it = data().begin(); it != data().end(); it++)
        total_num_of_particles += it->getNumOfParticles();
    return total_num_of_particles;
}

}
