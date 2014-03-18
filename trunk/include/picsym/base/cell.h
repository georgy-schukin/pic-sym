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
    size_t num_of_particles;
    std::list<Particle> particles;
    Rect2D<Real> bounds;

public:
    Cell(): id(0) {}
    Cell(const size_t& i, const size_t& num) : id(i), num_of_particles(num){}
    Cell(const size_t& i, const std::list<Particle>& p) : id(i), particles(p), num_of_particles(p.size()) {}
    ~Cell() {}
    
    void setNumOfParticles(const size_t& num) {
        num_of_particles = num;
    }

    void setParticles(const std::list<Particle>& p) {
        particles = p;
        num_of_particles = particles.size();
    }

    const size_t& getNumOfParticles() const {
        //return particles.size();
        return num_of_particles;
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

    void addParticles(const size_t& num) {
        num_of_particles += num;
    }

    void removeParticles(const size_t& num) {
        num_of_particles -= num;
    }

    //void addParticles(const std::list<Particle>& p);
    //std::list<Particles> removeParticles(const size_t& rem_num);

    Cell split(const size_t& load);
    Cell split();
    const Cell& merge(const Cell& cell);

    size_t getLoad() const;

    void compute();
};

}

