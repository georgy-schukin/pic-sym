#pragma once

#include <cstddef>
#include <vector>
#include <list>
#include "particle.h"

namespace picsym {

/**
 * @brief Cell in a mesh. Contains particles
 */
class Cell {
private:
    size_t id;
    //size_t num_of_particles;
    std::list<Particle> particles;

public:
    Cell(): id(0) {}
    Cell(const size_t& i, const std::list<Particle>& p) : id(i), particles(p) {}
    Cell(const Cell& c) : id(c.id), particles(c.particles) {}
    ~Cell() {}
    
    /*void setNumOfParticles(const size_t& num) {
        num_of_particles = num;
    }*/

    void setParticles(const std::list<Particle>& p) {
        particles = p;
    }

    const size_t& getNumOfParticles() const {
        return particles.size();
    }

    void setId(const size_t& i) {
        id = i;
    }

    const size_t& getId() const {
        return id;
    }    

    void addParticles(const std::list<Particle>& p);
    std::list<Particles> removeParticles(const size_t& rem_num);

    Cell split(const size_t& load);
    Cell split();
    const Cell& merge(const Cell& cell);
    size_t getLoad() const;

    //void generateParticles(const size_t& num);
};

}

