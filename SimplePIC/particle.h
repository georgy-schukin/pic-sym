#pragma once

#include "vector2d.h"

/**
  * Particle has coordinate in space and velocity
  */
class Particle {
public:
    Vector2D coordinate;
    Vector2D velocity;

public:
    Particle () {}
    Particle(const Vector2D &c, const Vector2D &v) : coordinate(c), velocity(v) {}
    ~Particle() {}
};
