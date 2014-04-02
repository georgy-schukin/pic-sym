#include "body.h"
#include <cmath>
#include <cstdlib>

void Body::init(const Rect2D &area) {
    coordinate.x = area.left + area.width() * double(rand() % 1000) / 1000.0;
    coordinate.y = area.bottom + area.height() * double(rand() % 1000) / 1000.0;
    velocity.x = double(rand() % 2000 - 1000) / 1000.0;
    velocity.y = double(rand() % 2000 - 1000) / 1000.0;
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
