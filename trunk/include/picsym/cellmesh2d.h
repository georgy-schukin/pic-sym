#pragma once

#include "base/mesh2d.h"
#include "base/cell.h"
#include "base/cellrange.h"
#include "base/rect2d.h"
#include "base/defines.h"
#include <QGraphicsScene>

namespace picsym {

class CellMesh2D : public Mesh2D<Cell>
{   
private:
    Rect2D<Real> bounds;

private:
    void init();
    std::list<Particle> generateExplosionParticles(const size_t& x, const size_t& y, const size_t& max_value);

public:
    CellMesh2D() {}
    CellMesh2D(const size_t& w, const size_t& h, const Rect2D<Real>& bnd) : Mesh2D(w, h), bounds(bnd) {
        init();
    }    
    CellMesh2D(const CellMesh2D& m) : Mesh2D(m), bounds(m.bounds) {
        init();
    }
    ~CellMesh2D() {}

    const Rect2D<Real>& getBounds() const {
        return bounds;
    }

    size_t getNumOfCells() const {
        return data().getSize();
    }

    size_t getNumOfParticles() const;

    CellRange getRange(const size_t& start, const size_t& end) const;

    void generateExplosion(const size_t& max_value);

    void draw(QGraphicsScene& scene);
};

}
