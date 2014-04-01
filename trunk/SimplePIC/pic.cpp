#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "cellmesh.h"

void generateParticles(CellMesh &mesh, const int &max_particles_in_cell_num) {
    for (CellMesh::iterator it = mesh.begin(); it != mesh.end(); it++) {
        it->generateParticles(max_particles_in_cell_num);
    }
}

void compute(CellMesh &mesh) {
    for (CellMesh::iterator it = mesh.begin(); it != mesh.end(); it++) {
        it->compute(mesh.getBound());
    }
}

void moveParticles(CellMesh &mesh) {
    ParticleList lost_particles;

    for (CellMesh::iterator it = mesh.begin(); it != mesh.end(); it++) {
        it->removeLostParticles(lost_particles);
    }

    for (ParticleList::const_iterator it = lost_particles.begin(); it != lost_particles.end(); it++) {
        mesh.addParticleInCell(*it);
    }
}

int main(int argc, char **argv)
{
    const int MESH_WIDTH_DEFAULT = 32;
    const int MESH_HEIGHT_DEFAULT = 32;
    const int MAX_ITER_DEFAULT = 10;
    const int MAX_PARTICLE_NUM_DEFAULT = 100;

    // Read arguments from command line
    const int mesh_width = (argc > 1) ? atoi(argv[1]) : MESH_WIDTH_DEFAULT;
    const int mesh_height = (argc > 2) ? atoi(argv[2]) : MESH_HEIGHT_DEFAULT;
    const int max_iter = (argc > 3) ? atoi(argv[3]) : MAX_ITER_DEFAULT;
    const int max_particle_num = (argc > 4) ? atoi(argv[4]) : MAX_PARTICLE_NUM_DEFAULT;

    printf("Mesh: %dx%d, iterations: %d\n", mesh_width, mesh_height, max_iter);

    // Create mesh of cells
    CellMesh mesh(mesh_width, mesh_height, Rect2D(-10, 10, -10, 10));

    // Fill mesh with particles
    generateParticles(mesh, max_particle_num);

    // Do computations
    for (int n = 0; n < max_iter; n++) {
        compute(mesh);
        moveParticles(mesh);
        printf("Iteration: %d, Num of particles: %d\n", n, mesh.getNumOfParticles());
    }

    return 0;
}
