#include "domain2d.h"

int Domain2D::detectQuadrant(const Vector2D &point) const {
    const Vector2D center(left + width() / 2.0, bottom + height() / 2.0); // center of domain

    const bool west = (point.x <= center.x);
    const bool north = (center.y <= point.y);

    if (north)
        return west ? NORTH_WEST : NORTH_EAST;
    else
        return west ? SOUTH_WEST : SOUTH_EAST;
}

Domain2D Domain2D::getQuadrant(const int &quadrant) const {

    const Vector2D center(left + width() / 2.0, bottom + height() / 2.0); // center of domain

    switch (quadrant) {
    case NORTH_WEST:
        return Domain2D(left, center.x, center.y, top);
    case NORTH_EAST:
        return Domain2D(center.x, right, center.y, top);
    case SOUTH_WEST:
        return Domain2D(left, center.x, bottom, center.y);
    case SOUTH_EAST:
        return Domain2D(center.x, right, bottom, center.y);
    default:
        return Domain2D(0.0, 0.0, 0.0, 0.0); // error - unknown domain id
    }
}

void Domain2D::expand(const Vector2D &point) {
    if (point.x < left)
        left = point.x;
    if (point.x > right)
        right = point.x;
    if (point.y < bottom)
        bottom = point.y;
    if (point.y > top)
        top = point.y;
}
