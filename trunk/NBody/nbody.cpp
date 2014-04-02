#include "body.h"
#include "rect2d.h"
#include <vector>
#include <cstdio>
#include <ctime>

typedef std::vector<Body> BodyArray;

void initBodies(BodyArray &bodies, const Rect2D &area) {
    for (BodyArray::iterator it = bodies.begin(); it != bodies.end(); it++) {
        it->init(area);
    }
}

void computeForces(BodyArray &bodies) {            
    for (BodyArray::iterator it = bodies.begin(); it != bodies.end(); it++) {

        it->force.set(0.0, 0.0); // null force

        for (BodyArray::iterator it2 = it + 1; it2 != bodies.end(); it2++) {
            const Vector2D fij = it->computeForce(*it2);
            it->force += fij;
            it2->force -= fij; // Fij = -Fji
        }
    }
}

void updateBodies(BodyArray &bodies, const double &dt) {
    for (BodyArray::iterator it = bodies.begin(); it != bodies.end(); it++) {
        it->update(dt);
    }
}

int main(int argc, char **argv) {

    const int NUM_OF_BODIES_DEFAULT = 1000;
    const int NUM_OF_TIME_STEPS_DEFAULT = 10;

    const int num_of_bodies = (argc > 1) ? atoi(argv[1]) : NUM_OF_BODIES_DEFAULT;
    const int num_of_time_steps = (argc > 2) ? atoi(argv[2]) : NUM_OF_TIME_STEPS_DEFAULT;
    const double delta_time = 0.01;

    printf("Bodies: %d, time steps: %d\n", num_of_bodies, num_of_time_steps);

    BodyArray bodies(num_of_bodies);

    clock_t c_beg = clock();

    initBodies(bodies, Rect2D(-10, 10, -10, 10));

    for (int t = 0; t < num_of_time_steps; t++) {
        computeForces(bodies);
        updateBodies(bodies, delta_time);
    }

    clock_t c_end = clock();

    printf("Time to compute: %.5f seconds\n", float(c_end - c_beg)/CLOCKS_PER_SEC);

    return 0;
}

