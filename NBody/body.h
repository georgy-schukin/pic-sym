#pragma once

#include "vector2d.h"
#include "rect2d.h"

/**
  * Body has coordinate in space, mass and force
  */
class Body {
public:
    Vector2D coordinate;
    Vector2D velocity;
    Vector2D force;
    double mass;

public:
    Body () {}
    Body(const Vector2D &c, const Vector2D &v, const double &m) : coordinate(c), velocity(v), mass(m) {}
    ~Body() {}

    void init(const Rect2D &area); // init coordinate, mass and velocity
    Vector2D computeForce(const Body &other) const; // compute force between this body and other body
    void update(const double &dt); // update coordinate and velocity
};
