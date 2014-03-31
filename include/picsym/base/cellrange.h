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
    typedef std::list<Cell>::iterator iterator;
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

    iterator begin() {
        return cells.begin();
    }

    iterator end() {
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

    size_t getSize() const {
        return cells.size();
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

    Cell splitFront(const LoadType& load);
    Cell splitBack(const LoadType& load);
    Cell split(const LoadType& load, const bool& from_back = true);
};

}
