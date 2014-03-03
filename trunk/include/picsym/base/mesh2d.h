#pragma once

#include "array.h"
#include "coord2d.h"

namespace picsym {

/**
 * @brief 2D mesh of cells
 */
template <class T>
class Mesh2D {
protected:
    Array<T> elems;

private:
    size_t width;
    size_t height;

public:
    Mesh2D() : width(0), height(0) {}
    Mesh2D(const size_t& w, const size_t& h) : width(w), height(h) {
        elems.resize(width*height);
    }
    ~Mesh2D() {}

    void setDimensions(const size_t& w, const size_t& h) {
        width = w;
        height = h;
        elems.resize(width*height);
    }      

    const size_t& getWidth() const {
        return width;
    }

    const size_t& getHeight() const {
        return height;
    }    

    const T& operator()(const size_t& row, const size_t& col) const {
        return elems.at(row*width + col);
    }

    T& operator()(const size_t& row, const size_t& col) {
        return elems.at(row*width + col);
    }

    const T& operator()(const Coord2D& c) const {
        return elems.at(c.getY()*width + c.getX());
    }

    T& operator()(const Coord2D& c) {
        return elems.at(c.getY()*width + c.getX());
    }

    const Array<T>& data() const {
        return elems;
    }
};

}

