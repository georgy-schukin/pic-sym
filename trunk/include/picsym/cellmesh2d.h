#pragma once

#include "base/mesh2d.h"
#include "base/cell.h"
#include "base/cellrange.h"
#include <QGraphicsScene>

namespace picsym {

class CellMesh2D : public Mesh2D<Cell>
{   
public:
    CellMesh2D() {}
    CellMesh2D(const size_t& w, const size_t& h) : Mesh2D(w, h) {}
    ~CellMesh2D() {}

    size_t getNumOfCells() const {
        return data().getSize();
    }

    CellRange getRange(const size_t& start, const size_t& end) const;

    void initIds();

    void initExplosion(const size_t& max_value);

    void draw(QGraphicsScene& scene);
};

}
