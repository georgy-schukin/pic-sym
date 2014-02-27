#pragma once

#include "base/list.h"
#include "base/cell.h"
#include "cellmesh2d.h"
#include <vector>
#include <cstddef>

namespace picsym {

/**
 * @brief Range of cells in Hilbert curve space
 */
class CellRange
{
private:    
    List<Cell> cells;
    size_t range_start; // start index for the cell array (by Hilbert distance, for example)
    size_t range_end; // end index for the array

public:
    CellRange() : range_start(0), range_end(0) {}
    CellRange(const CellMesh2D& mesh, const size_t& start, const size_t& end) {
        initByHilbert(mesh, start, end);
    }

    ~CellRange() {}

    void initByHilbert(const CellMesh2D& mesh, const size_t& start, const size_t& end);
};

}
