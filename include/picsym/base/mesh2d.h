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
    Mesh2D(const Mesh2D<T>& m) : width(m.width), height(m.height), elems(m.elems) {}
    ~Mesh2D() {}

    const size_t& getWidth() const {
        return width;
    }

    const size_t& getHeight() const {
        return height;
    }    

    const T& operator()(const size_t& x, const size_t& y) const {
        return elems.at(y*width + x);
    }

    T& operator()(const size_t& x, const size_t& y) {
        return elems.at(y*width + x);
    }

    const T& operator()(const Coord2D<size_t>& c) const {
        return elems.at(c.getY()*width + c.getX());
    }

    T& operator()(const Coord2D<size_t>& c) {
        return elems.at(c.getY()*width + c.getX());
    }

    const Array<T>& data() const {
        return elems;
    }
};

}

