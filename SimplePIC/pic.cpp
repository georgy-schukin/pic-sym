#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "cellmesh.h"

void generateParticles(CellMesh &mesh) {
    for (Cell &cell : mesh) {
        cell.addParticles(ParticleList(rand() % 100 + 1)); // generate from 1 to 100 particles in cell

        for (Particle &particle : cell.particles) {
            particle.coordinate.x = cell.bound.left + cell.bound.width() * double(rand() % 100) / 100.0; // random coord
            particle.coordinate.y = cell.bound.bottom + cell.bound.height() * double(rand() % 100) / 100.0;
            particle.velocity.x = cell.bound.width() * double(rand() % 100 - 200) / 1000.0; // random velocity
            particle.velocity.y = cell.bound.height() * double(rand() % 100 - 200) / 1000.0;
        }
    }
}

void compute(CellMesh &mesh) {
    for (Cell &cell : mesh) {
        cell.compute(mesh.getBound());
    }
}

void moveParticles(CellMesh &mesh) {
    ParticleList lost_particles;
    for (Cell &cell : mesh) {
        cell.removeLostParticles(lost_particles);
    }

    for (const Particle &particle : lost_particles) {
        const int index = mesh.getCellIndex(particle.coordinate);
        if (index != -1) {
            mesh.at(index).addParticle(particle); // add particle to new cell
        } else {
            printf("Lost %f %f\n", particle.coordinate.x, particle.coordinate.y);
        }
    }
}

int main(int argc, char **argv)
{
    const int MESH_WIDTH_DEFAULT = 32;
    const int MESH_HEIGHT_DEFAULT = 15;
    const int MAX_ITER_DEAFULT = 100;

    // Read arguments from command line
    int mesh_width = (argc > 1) ? atoi(argv[1]) : MESH_WIDTH_DEFAULT;
    int mesh_height = (argc > 2) ? atoi(argv[2]) : MESH_HEIGHT_DEFAULT;
    int max_iter = (argc > 3) ? atoi(argv[3]) : MAX_ITER_DEAFULT;

    printf("Mesh: %dx%d, iterations: %d\n", mesh_width, mesh_height, max_iter);

    // Create mesh of cells
    CellMesh mesh(mesh_width, mesh_height, Rect2D(-10, 10, -10, 10));

    // Fill mesh with particles
    generateParticles(mesh);

    // Do computations
    for (int n = 0; n < max_iter; n++) {
        compute(mesh);
        moveParticles(mesh);
        printf("Iteration: %d, Num of particles: %d\n", n, mesh.getNumOfParticles());
    }

    return 0;
}
