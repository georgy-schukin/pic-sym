#pragma once

#include <cstddef>

namespace picsym {

/**
 * @brief Cell in a mesh. Contains particles
 */
class Cell {
private:
    size_t num_of_particles;
    size_t id;
    
public:
    Cell(): num_of_particles(0), id(0) {}
    Cell(const size_t& i, const size_t& num) : id(i), num_of_particles(num) {}
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
};

}

