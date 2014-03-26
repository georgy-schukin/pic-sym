#include "picsym/base/cell.h"

namespace picsym {

void Cell::addParticles(const std::list<Particle>& p) {
    particles.insert(particles.end(), p.begin(), p.end());
}

void Cell::removeParticles(const size_t& rem_num, std::list<Particle>& removed) {
    for (size_t i = 0; (i < rem_num) && !particles.empty(); i++) {
        removed.push_back(particles.back());
        particles.pop_back();
    }
}

Cell Cell::split(const size_t& load) {
    const size_t particles_to_take = load;
    std::list<Particle> removed_particles;
    removeParticles(particles_to_take, removed_particles);
    return Cell(getId(), removed_particles);
}

Cell Cell::split() {
    return split(getNumOfParticles()/2);
}

const Cell& Cell::merge(const Cell& cell) {
    addParticles(cell.getParticles());
    return *this;
}

size_t Cell::getLoad() const {
    return getNumOfParticles();
}

void Cell::compute() {
    for (std::list<Particle>::iterator it = particles.begin(); it != particles.end(); it++) {
        it->setCoordinate(it->getCoordinate() + it->getVelocity());
    }
    iter_num++;
}

}
