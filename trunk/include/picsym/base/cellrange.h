#pragma once

#include "cell.h"
#include <list>
#include <cstddef>

namespace picsym {

/**
 * @brief Range of cells
 */
class CellRange
{
public:
    typedef std::list<Cell>::const_iterator const_iterator;
    typedef std::list<Cell>::const_reverse_iterator const_reverse_iterator;

private:    
    std::list<Cell> cells;

public:
    CellRange() {}        
    CellRange(const CellRange& r) : cells(r.cells) {}
    ~CellRange() {}  

    const std::list<Cell>& getCells() const {
        return cells;
    }

    const_iterator begin() const {
        return cells.begin();
    }

    const_iterator end() const {
        return cells.end();
    }

    const_reverse_iterator rbegin() const {
        return cells.rbegin();
    }

    const_reverse_iterator rend() const {
        return cells.rend();
    }

    bool isEmpty() const {
        return cells.empty();
    }

    const Cell& back() const {
        return cells.back();
    }

    const Cell& front() const {
        return cells.front();
    }

    size_t getFrontId() const;
    size_t getBackId() const;

    void add(const Cell& cell);
    void add(const CellRange& cell_range);

    Cell removeFromFront();
    Cell removeFromBack();
    Cell remove(const bool& from_back = true);

    Cell splitFront(const size_t& particles_to_take);
    Cell splitBack(const size_t& particles_to_take);
    Cell split(const size_t& particles_to_take, const bool& from_back = true);
};

}
