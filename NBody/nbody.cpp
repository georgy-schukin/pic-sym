#include "body.h"
#include "domain2d.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>

void initBodies(Body *bodies, const int &num_of_bodies, const Domain2D &domain) {
    for (int i = 0; i < num_of_bodies; i++) {
        bodies[i].init(domain);
    }
}

void computeForces(Body *bodies, const int &num_of_bodies) {
    for (int i = 0; i < num_of_bodies; i++) {

        bodies[i].force = 0.0; // null force

        for (int j = i + 1; j < num_of_bodies; j++) {
            const Vector2D force_ij = bodies[i].computeForce(bodies[j]);
            bodies[i].force += force_ij;
            bodies[j].force -= force_ij; // Fij = -Fji
        }
    }
}

void updateBodies(Body *bodies, const int &num_of_bodies, const double &dt) {
    for (int i = 0; i < num_of_bodies; i++) {
        bodies[i].update(dt);
    }
}

int main(int argc, char **argv) {

    const int NUM_OF_BODIES_DEFAULT = 1000;
    const int NUM_OF_TIME_STEPS_DEFAULT = 10;

    const int num_of_bodies = (argc > 1) ? atoi(argv[1]) : NUM_OF_BODIES_DEFAULT;
    const int num_of_time_steps = (argc > 2) ? atoi(argv[2]) : NUM_OF_TIME_STEPS_DEFAULT;

    const double delta_t = 0.01;

    printf("Bodies: %d, time steps: %d\n", num_of_bodies, num_of_time_steps);

    Body *bodies = new Body[num_of_bodies];

    clock_t c_beg = clock();

    initBodies(bodies, num_of_bodies, Domain2D(-10, 10, -10, 10));

    for (int t = 0; t < num_of_time_steps; t++) {
        computeForces(bodies, num_of_bodies);
        updateBodies(bodies, num_of_bodies, delta_t);
    }

    clock_t c_end = clock();

    printf("Time to compute: %.5f seconds\n", float(c_end - c_beg)/CLOCKS_PER_SEC);

    delete[] bodies;

    return 0;
}

