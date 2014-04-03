#pragma once

/**
  * @brief Pair of two real values: x and y
  */
class Vector2D
{
public:
    double x;
    double y;

public:
    Vector2D() : x(0.0), y(0.0) {}
    Vector2D(const double &xx, const double &yy) : x(xx), y(yy) {}
    ~Vector2D() {}

    void set(const double &xx, const double &yy) {
        x = xx;
        y = yy;
    }

    void operator=(const double &val) {
        x = val;
        y = val;
    }

    void operator+=(const Vector2D &v) {
        x += v.x;
        y += v.y;
    }

    void operator-=(const Vector2D &v) {
        x -= v.x;
        y -= v.y;
    }    
};
