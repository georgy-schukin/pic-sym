#pragma once

#include "cell.h"
//#include "cellmesh2d.h"
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
    /*CellRange(const CellMesh2D& mesh, const size_t& start, const size_t& end) {
        initByHilbert(mesh, start, end);
    }*/

    ~CellRange() {}

  //  void initByHilbert(const CellMesh2D& mesh, const size_t& start, const size_t& end);

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

    size_t getStartId() const;
    size_t getEndId() const;

    void addToStart(const Cell& cell);
    void addToStart(const CellRange& cell_range);

    void addToEnd(const Cell& cell);
    void addToEnd(const CellRange& cell_range);

    Cell removeFromStart();
    Cell removeFromEnd();

    Cell separateStart(const size_t& particles_to_take);
    Cell separateEnd(const size_t& particles_to_take);
};

}
