#pragma once

#include <cstddef>

namespace picsym {

template<class T>
class Coord2D      
{
private:
    T x;
    T y;
public:
    Coord2D() : x(0), y(0) {}
    Coord2D(const T& xx, const T& yy) : x(xx), y(yy) {}
    Coord2D(const Coord2D<T>& c) : x(c.x), y(c.y) {}
    ~Coord2D() {}

    void set(const T& xx, const T& yy) {
        x = xx;
        y = yy;
    }

    const T& getX() const {
        return x;
    }

    const T& getY() const {
        return y;
    }

    void operator=(const Coord2D<T>& c) {
        x = c.getX();
        y = c.getY();
    }
};

}
