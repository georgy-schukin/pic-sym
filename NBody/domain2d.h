#pragma once

#include "vector2d.h"

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
};
