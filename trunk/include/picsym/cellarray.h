#pragma once

#include "picsym/cell.h"
#include <vector>

namespace picsym {

class CellArray
{
protected:
    std::vector<Cell> cells;

public:
    typedef std::vector<Cell>::iterator iterator;
    typedef std::vector<Cell>::const_iterator const_iterator;

public:
    CellArray() {}
    CellArray(const size_t& size) {
        resize(size);
    }
    ~CellArray() {}

    const size_t& getSize() const {
        return cells.size();
    }

    const Cell& operator[](const size_t& index) const {
        return cells[index];
    }

    Cell& operator[](const size_t& index) {
        return cells[index];
    }

    void resize(const size_t& size);
};

}
