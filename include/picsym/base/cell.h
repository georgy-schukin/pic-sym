#pragma once

#include <cstddef>

namespace picsym {

/**
 * @brief Cell in a mesh. Contains particles
 */
class Cell {
private:
    size_t id;
    size_t num_of_particles;

public:
    Cell(): id(0), num_of_particles(0) {}
    Cell(const size_t& i, const size_t& num) : id(i), num_of_particles(num) {}
    Cell(const Cell& c) : id(c.id), num_of_particles(c.num_of_particles) {}
    ~Cell() {}
    
    void setNumOfParticles(const size_t& num) {
        num_of_particles = num;
    }

    void addParticles(const size_t& add_num) {
        num_of_particles += add_num;
    }

    void removeParticles(const size_t& rem_num) {
        num_of_particles -= rem_num;
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

    Cell split(const size_t& particles_to_take);
    const Cell& merge(const Cell& cell);
};

}

