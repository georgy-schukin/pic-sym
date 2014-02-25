#pragma once

#include "picsym/cell.h"
#include <vector>

namespace picsym {

class Mesh2D {
private:
    std::vector<Cell> cells;
    size_t width;
    size_t height;

public:
    typedef std::vector<Cell>::iterator iterator;
    typedef std::vector<Cell>::const_iterator const_iterator;

public:
    Mesh2D() : width(0), height(0) {}
    Mesh2D(const size_t& w, const size_t& h) : width(w), height(h) {
        cells.resize(width*height, Cell());
    }
    ~Mesh2D() {}

    void setDimensions(const size_t& w, const size_t& h) {
        width = w;
        height = h;
        cells.resize(width*height, Cell());
    }

    const size_t& getWidth() const {
        return width;
    }

    const size_t& getHeight() const {
        return height;
    }

    const std::vector<Cell>& getCells() const {
        return cells;
    }

    size_t getNumOfCells() const {
        return width*height;
    }
};

}

