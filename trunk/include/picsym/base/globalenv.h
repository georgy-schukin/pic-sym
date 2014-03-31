#pragma once

#include <cstddef>

namespace picsym {

class GlobalEnvironment
{
private:
    size_t num_of_cells;
    size_t num_of_particles;
    size_t mesh_size;
    double balance_coeff;

public:
    GlobalEnvironment() : num_of_cells(0), num_of_particles(0), mesh_size(0), balance_coeff(0) {}
    GlobalEnvironment(const size_t& tnc, const size_t& tnp, const size_t& ms, const double& coeff) :
        num_of_cells(tnc), num_of_particles(tnp), mesh_size(ms), balance_coeff(coeff) {}
    GlobalEnvironment(const GlobalEnvironment& e) :
        num_of_cells(e.num_of_cells), num_of_particles(e.num_of_particles),
        mesh_size(e.mesh_size), balance_coeff(e.balance_coeff) {}
    ~GlobalEnvironment() {}

    void setTotalNumOfCells(const size_t& num) {
        num_of_cells = num;
    }

    void setTotalNumOfParticles(const size_t& num) {
        num_of_particles = num;
    }

    void setMeshSize(const size_t& num) {
        mesh_size = num;
    }

    void setBalanceCoeff(const double& coeff) {
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

    const double& getBalanceCoeff() const {
        return balance_coeff;
    }
};

const GlobalEnvironment& getGlobalEnvironment();
void setGlobalEnvironment(const GlobalEnvironment& env);

}
