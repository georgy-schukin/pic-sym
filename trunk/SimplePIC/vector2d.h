#pragma once

/**
  * Pair of two real values: x and y
  */
class Vector2D
{
public:
    double x;
    double y;

public:
    Vector2D() : x(0), y(0) {}
    Vector2D(const double &xx, const double &yy) : x(xx), y(yy) {}
    ~Vector2D() {}
};
