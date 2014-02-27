#pragma once

#include "array.h"
#include "cell.h"
#include <vector>
#include <QGraphicsScene>

namespace picsym {

/**
 * @brief 2D mesh of cells
 */
class Mesh2D : public Array<Cell> {
private:    
    size_t width;
    size_t height;

public:
    Mesh2D() : width(0), height(0) {}
    Mesh2D(const size_t& w, const size_t& h) : width(w), height(h) {
        resize(width*height);
    }
    ~Mesh2D() {}

    void setDimensions(const size_t& w, const size_t& h) {
        width = w;
        height = h;
        resize(width*height);
    }      

    const size_t& getWidth() const {
        return width;
    }

    const size_t& getHeight() const {
        return height;
    }    

    const Cell& operator()(const size_t& row, const size_t& col) const {
        return at(row*width + col);
    }

    Cell& operator()(const size_t& row, const size_t& col) {
        return at(row*width + col);
    }

    size_t getNumOfCells() const {
        return width*height;
    }

    void initExplosion(const size_t& max_value);

    void draw(QGraphicsScene& scene);
};

}

