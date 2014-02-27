#include "picsym/base/hilbert.h"

namespace picsym {

size_t Hilbert::coordToDistance(const size_t& x, const size_t& y, const size_t& mesh_size) {
    size_t dist = 0;
    size_t tx = x, ty = y;
    for (size_t s = mesh_size/2; s > 0; s /= 2) {
       const size_t rx = (tx & s) > 0;
       const size_t ry = (ty & s) > 0;
       dist += s * s * ((3 * rx) ^ ry);
       rotate(tx, ty, s, rx, ry);
    }
    return dist;
}

void Hilbert::distanceToCoord(const size_t& dist, const size_t& mesh_size, size_t& x, size_t& y) {
    x = y = 0;
    size_t t = dist;
    for (size_t s = 1; s < mesh_size; s *= 2) {
        const size_t rx = 1 & (t/2);
        const size_t ry = 1 & (t ^ rx);
        rotate(x, y, s, rx, ry);
        x += s * rx;
        y += s * ry;
        t /= 4;
    }
}

void Hilbert::rotate(size_t& x, size_t& y, const size_t& mesh_size, const size_t& rx, const size_t& ry) {
    if (ry == 0) {
        if (rx == 1) {
            x = mesh_size - 1 - x;
            y = mesh_size - 1 - y;
        }
        size_t temp = x;
        x = y;
        y = temp;
    }
}

}
