#include "picsym/base/particle.h"

namespace picsym {

void Particle::move() {
    coordinate.set(coordinate.getX() + velocity.getX(),
                   coordinate.getY() + velocity.getY());
}

}
