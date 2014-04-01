#include "cellmesh.h"
#include <cstdlib>

void CellMesh::init(const int &w, const int &h, const Rect2D &b) {
    width = w;
    height = h;
    bound = b;

    cell_width = bound.width()/width; // cell size by X
    cell_height = bound.height()/height; // cell size by Y

    cells.resize(width*height); // create array of cells

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            const double cx = bound.left + j*cell_width; // cell left coord by X (go RIGHT by j)
            const double cy = bound.bottom + i*cell_height; // cell top coord by Y (go UP by i)
            cells[i*width + j].bound = Rect2D(cx, cx + cell_width, cy, cy + cell_height); // set cell's bound
        }
    }
}

void CellMesh::addParticleInCell(const Particle &particle) {
    const int index = getCellIndex(particle.coordinate);
    if (index != -1)
        cells.at(index).addParticle(particle);
}

int CellMesh::getCellIndex(const Vector2D &coord) const {
    static const double EPS = 1e-9;
    const int ix = (fabs(coord.x - bound.right) < EPS) ? width - 1 : int((coord.x - bound.left) / cell_width); // get cell indices for coord
    const int iy = (fabs(coord.y - bound.top) < EPS) ? height - 1 : int((coord.y - bound.bottom) / cell_height);

    if ((ix >= 0) && (ix < width) && (iy >=0) && (iy < height)) { // particle is inside of mesh
        return iy*width + ix; // get cell index
    } else
        return -1;
}

int CellMesh::getNumOfParticles() const {
    int num = 0;
    for (CellMesh::const_iterator it = cells.begin(); it != cells.end(); it++) {
        num += it->particles.size();
    }
    return num;
}
