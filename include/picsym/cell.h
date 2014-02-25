#pragma once

namespace picsym {

class Cell {
private:
    size_t num_of_particles;
    size_t node;
    
public:
    Cell(): num_of_particles(0) {}
    ~Cell() {}
    
    void setNumOfParticles(const size_t& num) {
        num_of_particles = num;
    }
    
    const size_t& getNumOfParticles() const {
        return num_of_particles;
    }
};

}

