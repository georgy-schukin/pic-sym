#include "body.h"
#include <cmath>
#include <cstdlib>

void Body::init(const Domain2D &domain) {
    coordinate.x = domain.left + domain.width() * double(rand() % 100000) / 100000.0;
    coordinate.y = domain.bottom + domain.height() * double(rand() % 100000) / 100000.0;
    velocity.x = double(rand() % 200000 - 100000) / 100000.0;
    velocity.y = double(rand() % 200000 - 100000) / 100000.0;
    mass = double(rand() % 1000 + 10) / 100.0; // avoid zero mass
}

Vector2D Body::computeForce(const Body &other) const {
    static const double G = 6.673e-11;

    const double dx = other.coordinate.x - coordinate.x;
    const double dy = other.coordinate.y - coordinate.y;
    const double dist = sqrt(dx*dx + dy*dy) + 1e-12; // avoid zero distance
    const double temp = G*other.mass*mass/(dist*dist*dist);

    return Vector2D(temp*dx, temp*dy);
}

void Body::update(const double &dt) {
    coordinate.x += dt*velocity.x; // update coordinate
    coordinate.y += dt*velocity.y;
    velocity.x += dt*force.x/mass; // update velocity
    velocity.y += dt*force.y/mass;
}
