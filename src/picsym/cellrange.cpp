#include "picsym/cellrange.h"
#include "picsym/base/hilbert.h"

namespace picsym {

void CellRange::initByHilbert(const CellMesh2D& mesh, const size_t& start, const size_t& end) {
    range_start = start;
    range_end = end;

    //cells.resize(end - start);

    const size_t& mesh_size = mesh.getWidth();

    for (size_t dist = range_start; dist < range_end; dist++) {
        size_t x = 0, y = 0;
        Hilbert::distanceToCoord(dist, mesh_size, x, y);     
        //cells.at(dist - range_start) = mesh(y, x);
    }
}

}
