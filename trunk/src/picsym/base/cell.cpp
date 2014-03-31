#include "picsym/base/cell.h"
#include "picsym/base/globalenv.h"

namespace picsym {

void Cell::addParticle(const Particle& p) {
    particles.push_back(p);
}

void Cell::addParticles(const std::list<Particle>& p) {
    particles.insert(particles.end(), p.begin(), p.end());
}

Particle Cell::removeParticle() {
    Particle removed = particles.back();
    particles.pop_back();
    return removed;
}

void Cell::removeParticles(const size_t& rem_num, std::list<Particle>& removed) {
    for (size_t i = 0; (i < rem_num) && !particles.empty(); i++) {
        removed.push_back(particles.back());
        particles.pop_back();
    }
}

Cell Cell::split(const LoadType& load) {
    Cell split_cell(getId());
    while ((split_cell.getLoad() < load) && !particles.empty()) {
        split_cell.addParticle(removeParticle());
    }
    return split_cell;
}

const Cell& Cell::merge(const Cell& cell) {
    addParticles(cell.getParticles());
    return *this;
}

LoadType Cell::getLoad() const {
    const GlobalEnvironment& env = GlobalEnvironment::get();
    const LoadType& coeff = env.getBalanceCoeff();
    return coeff*LoadType(getNumOfParticles())/LoadType(env.getTotalNumOfParticles()) + (1.0 - coeff);
    //return getNumOfParticles();
}

void Cell::compute() {
    for (std::list<Particle>::iterator it = particles.begin(); it != particles.end(); it++) {
        it->setCoordinate(it->getCoordinate() + it->getVelocity());
    }
    iter_num++;
}

}
