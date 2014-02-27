#include "picsym/meshpart.h"
#include "picsym/hilbert.h"

namespace picsym {

void MeshPart::initByHilbert(const Mesh2D& mesh, const size_t& start, const size_t& end) {
    index_start = start;
    index_end = end;

    resize(end - start);

    const size_t& mesh_size = mesh.getWidth();

    for (size_t dist = index_start; dist < index_end; dist++) {
        size_t x = 0, y = 0;
        Hilbert::distanceToCoord(dist, mesh_size, x, y);
        at(dist - index_start) = mesh(y, x);
    }
}

}
