#pragma once

#include "coord2d.h"
#include "defines.h"

namespace picsym {

/**
 * @brief Particle. Has coordinate and velocity
 */
class Particle {
private:
    Coord2D<Real> coordinate;
    Coord2D<Real> velocity;

public:
    Particle() {}
    Particle(const Coord2D<Real>& c, const Coord2D<Real>& v) : coordinate(c), velocity(v) {}
    ~Particle() {}

    void setCoordinate(const Coord2D<Real>& coord) {
        coordinate = coord;
    }

    const Coord2D<Real>& getCoordinate() const {
        return coordinate;
    }

    void setVelocity(const Coord2D<Real>& vel) {
        velocity = vel;
    }

    const Coord2D<Real>& getVelocity() const {
        return velocity;
    }

    void move();
};

}
