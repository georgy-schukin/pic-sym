#pragma once

#include "array.h"
#include "mesh2d.h"
#include "cell.h"
#include <vector>
#include <cstddef>

namespace picsym {

/**
 * @brief Part of a cell mesh on a node
 */
class MeshPart : public Array<Cell>
{
private:    
    size_t index_start; // start index for the cell array (by Hilbert distance, for example)
    size_t index_end; // end index for the array

public:
    MeshPart() : index_start(0), index_end(0) {}
    MeshPart(const Mesh2D& mesh, const size_t& start, const size_t& end) {
        initByHilbert(mesh, start, end);
    }

    ~MeshPart() {}

    void initByHilbert(const Mesh2D& mesh, const size_t& start, const size_t& end);    
};

}
