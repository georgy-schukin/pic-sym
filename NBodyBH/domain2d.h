#pragma once

#include "vector2d.h"

#define NORTH_WEST 0
#define NORTH_EAST 1
#define SOUTH_WEST 2
#define SOUTH_EAST 3

/**
  * @brief 2D domain is defined by left and right (by X) and bottom and top (by Y)
  */
class Domain2D
{
public:
    double left;
    double right;
    double bottom;
    double top;       

public:
    Domain2D() {}
    Domain2D(const double &l, const double &r, const double &b, const double &t) : left(l), right(r), bottom(b), top(t) {}
    ~Domain2D() {}

    double width() const {
        return right - left;
    }

    double height() const {
        return top - bottom;
    }    

    int detectQuadrant(const Vector2D &point) const;
    Domain2D getQuadrant(const int &quadrant) const;
};
