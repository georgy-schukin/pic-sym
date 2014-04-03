#include "tree.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>

void initBodies(Body *bodies, const int &num_of_bodies, const Domain2D &area) {
    for (int i = 0; i < num_of_bodies; i++) {
        bodies[i].init(area);
    }
}

void computeForces(Body *bodies, const int &num_of_bodies, const Tree &tree, const double &theta) {
    for (int i = 0; i < num_of_bodies; i++) {
        bodies[i].force = tree.computeForce(&bodies[i], theta);
    }
}

void updateBodies(Body *bodies, const int &num_of_bodies, const double &dt) {
    for (int i = 0; i < num_of_bodies; i++) {
        bodies[i].update(dt);		
    }
}

Domain2D& expandDomain(Domain2D &domain, Body *bodies, const int &num_of_bodies) {
	for (int i = 0; i < num_of_bodies; i++) {
        domain.expand(bodies[i].coordinate);
	}	
    return domain;
}

int main(int argc, char **argv) {

    const int NUM_OF_BODIES_DEFAULT = 100000;
    const int NUM_OF_TIME_STEPS_DEFAULT = 10;

    const int num_of_bodies = (argc > 1) ? atoi(argv[1]) : NUM_OF_BODIES_DEFAULT;
    const int num_of_time_steps = (argc > 2) ? atoi(argv[2]) : NUM_OF_TIME_STEPS_DEFAULT;

    const double delta_t = 0.01;
    const double theta = 1.0;

    printf("Bodies: %d, time steps: %d\n", num_of_bodies, num_of_time_steps);

    Body *bodies = new Body[num_of_bodies];

    clock_t c_beg = clock();

    Domain2D domain(-10.0, 10.0, -10.0, 10.0);

    initBodies(bodies, num_of_bodies, domain);

    for (int t = 0; t < num_of_time_steps; t++) {        
        Tree tree(bodies, num_of_bodies, expandDomain(domain, bodies, num_of_bodies));
        computeForces(bodies, num_of_bodies, tree, theta);
        updateBodies(bodies, num_of_bodies, delta_t);
        //printf("%d %d\n", tree.getHeight(), tree.getSize());
    }

    clock_t c_end = clock();

    printf("Time to compute: %.5f seconds\n", float(c_end - c_beg)/CLOCKS_PER_SEC);

    delete[] bodies;

    return 0;
}

