#pragma once

#include <cstddef>

namespace picsym {

class Coord2D
{
private:
    size_t x;
    size_t y;
public:
    Coord2D() : x(0), y(0) {}
    Coord2D(const size_t& xx, const size_t& yy) : x(xx), y(yy) {}
    ~Coord2D() {}

    void set(const size_t& xx, const size_t& yy) {
        x = xx;
        y = yy;
    }

    const size_t& getX() const {
        return x;
    }

    const size_t& getY() const {
        return y;
    }
};

}
