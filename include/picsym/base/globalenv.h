#pragma once

#include "defines.h"

namespace picsym {

class GlobalEnvironment
{
private:
    size_t num_of_cells;
    size_t num_of_particles;
    size_t mesh_size;
    LoadType balance_coeff;

private:
    GlobalEnvironment() : num_of_cells(0), num_of_particles(0), mesh_size(0), balance_coeff(0) {}
    ~GlobalEnvironment() {}

public:
    static GlobalEnvironment& get();

    void setTotalNumOfCells(const size_t& num) {
        num_of_cells = num;
    }

    void setTotalNumOfParticles(const size_t& num) {
        num_of_particles = num;
    }

    void setMeshSize(const size_t& num) {
        mesh_size = num;
    }

    void setBalanceCoeff(const LoadType& coeff) {
        balance_coeff = coeff;
    }

    const size_t& getTotalNumOfCells() const {
        return num_of_cells;
    }

    const size_t& getTotalNumOfParticles() const {
        return num_of_particles;
    }

    const size_t& getMeshSize() const {
        return mesh_size;
    }

    const LoadType& getBalanceCoeff() const {
        return balance_coeff;
    }
};

}
