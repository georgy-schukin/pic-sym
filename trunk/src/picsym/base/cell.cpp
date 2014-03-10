#include "picsym/base/cell.h"

namespace picsym {

void Cell::addParticles(const std::list<Particle>& p) {
    particles.insert(particles.end(), p.begin(), p.end());
}

std::list<Particles> Cell::removeParticles(const size_t& rem_num) {
    //num_of_particles -= rem_num;
}

Cell Cell::split(const size_t& load) {
    const size_t particles_to_take = load;
    Cell new_cell(getId(), particles_to_take);
    removeParticles(particles_to_take);
    return new_cell;
}

Cell Cell::split() {
    const size_t particles_to_take = getNumOfParticles()/2; // split in half
    Cell new_cell(getId(), particles_to_take);
    removeParticles(particles_to_take);
    return new_cell;
}

const Cell& Cell::merge(const Cell& cell) {
    addParticles(cell.getNumOfParticles());
    return *this;
}

size_t Cell::getLoad() const {
    return num_of_particles;
}

}
