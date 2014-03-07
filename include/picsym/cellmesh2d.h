#pragma once

#include "base/mesh2d.h"
#include "base/cell.h"
#include "base/cellrange.h"
#include <QGraphicsScene>

namespace picsym {

class CellMesh2D : public Mesh2D<Cell>
{   
private:
    void initIds();

public:
    CellMesh2D() {}
    CellMesh2D(const size_t& w, const size_t& h) : Mesh2D(w, h) {
        initIds();
    }
    ~CellMesh2D() {}

    void init(const size_t& width, const size_t& height);

    size_t getNumOfCells() const {
        return data().getSize();
    }

    CellRange getRange(const size_t& start, const size_t& end) const;
    size_t getNumOfParticles() const;

    void generateExplosion(const size_t& max_value);

    void draw(QGraphicsScene& scene);
};

}
