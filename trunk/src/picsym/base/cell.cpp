#include "picsym/base/cell.h"

namespace picsym {

Cell Cell::split(const size_t& particles_to_take) {
    Cell new_cell(getId(), particles_to_take);
    removeParticles(particles_to_take);
    return new_cell;
}

const Cell& Cell::merge(const Cell& cell) {
    addParticles(cell.getNumOfParticles());
    return *this;
}

}
