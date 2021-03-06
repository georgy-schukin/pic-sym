#pragma once

#include "vector2d.h"

/**
  * 2D rectangle is defined by left and right (by X) and bottom and top (by Y).
  * Usually right > left and top > bottom
  */
class Rect2D
{
public:
    double left;
    double right;
    double bottom;
    double top;

public:
    Rect2D() {}
    Rect2D(const double &l, const double &r, const double &b, const double &t) : left(l), right(r), bottom(b), top(t) {}
    ~Rect2D() {}

    double width() const {
        return right - left;
    }

    double height() const {
        return top - bottom;
    }

    bool isInside(const Vector2D &point) const {        
        static const double EPS = 1e-9;
        if ((point.x < left - EPS) || (point.x > right + EPS) || (point.y < bottom - EPS) || (point.y > top + EPS))
            return false;
        else
            return true;
    }
};
