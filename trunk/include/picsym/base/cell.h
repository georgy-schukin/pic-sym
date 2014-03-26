#pragma once

#include <cstddef>
#include <vector>
#include <list>
#include "particle.h"
#include "rect2d.h"

namespace picsym {

/**
 * @brief Cell in a mesh. Contains particles
 */
class Cell {
private:
    size_t id;
    //size_t num_of_particles;
    std::list<Particle> particles;
    Rect2D<Real> bounds;
    size_t iter_num;

public:
    Cell(): id(0), iter_num(0) {}
    Cell(const size_t& i, const std::list<Particle>& p) : id(i), particles(p) {}
    ~Cell() {}       

    void setParticles(const std::list<Particle>& p) {
        particles = p;        
    }

    const std::list<Particle>& getParticles() const {
        return particles;
    }

    size_t getNumOfParticles() const {
        return particles.size();
    }

    void setId(const size_t& i) {
        id = i;
    }

    const size_t& getId() const {
        return id;
    }    

    void setBounds(const Rect2D<Real>& bnd) {
        bounds = bnd;
    }

    const Rect2D<Real>& getBounds() {
        return bounds;
    }

    /*void addParticles(const size_t& num) {
        num_of_particles += num;
    }

    void removeParticles(const size_t& num) {
        num_of_particles -= num;
    }*/

    void addParticles(const std::list<Particle>& p);
    void removeParticles(const size_t& rem_num, std::list<Particle>& removed);

    Cell split(const size_t& load);
    Cell split();
    const Cell& merge(const Cell& cell);

    size_t getLoad() const;

    void compute();
};

}

