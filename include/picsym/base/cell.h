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
    size_t num_of_particles;
    std::list<Particle> particles;

public:
    Cell(): id(0), num_of_particles(0) {}
    Cell(const size_t& i, const size_t& num) : id(i), num_of_particles(num) {}
    Cell(const Cell& c) : id(c.id), num_of_particles(c.num_of_particles) {}
    ~Cell() {}
    
    void setNumOfParticles(const size_t& num) {
        num_of_particles = num;
    }
    
    const size_t& getNumOfParticles() const {
        return num_of_particles;
    }

    void setId(const size_t& i) {
        id = i;
    }

    const size_t& getId() const {
        return id;
    }

    void addParticles(const size_t& add_num) {
        num_of_particles += add_num;
    }

    //void addParticles(const Array<Particle>& particles)

    void removeParticles(const size_t& rem_num) {
        num_of_particles -= rem_num;
    }

    Cell split(const size_t& load);
    Cell split();
    const Cell& merge(const Cell& cell);
    size_t getLoad() const;

    void generateParticles(const size_t& num);
};

}

