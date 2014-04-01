#include "cell.h"
#include <cstdlib>

void Cell::generateParticles(const int &max_num) {
    particles.resize(rand() % max_num); // create maximum max_num-1 particles
    for (ParticleList::iterator it = particles.begin(); it != particles.end(); it++) {
        Particle &particle = *it;
        particle.coordinate.x = bound.left + bound.width() * double(rand() % 100) / 100.0; // random coord
        particle.coordinate.y = bound.bottom + bound.height() * double(rand() % 100) / 100.0;
        particle.velocity.x = bound.width() * double(rand() % 100 - 200) / 1000.0; // random velocity
        particle.velocity.y = bound.height() * double(rand() % 100 - 200) / 1000.0;
    }
}

void Cell::compute(const Rect2D &mesh_bound) {
    for (ParticleList::iterator it = particles.begin(); it != particles.end(); it++) {
        Particle &particle = *it;

        Vector2D new_coordinate(particle.coordinate.x + particle.velocity.x,
                                particle.coordinate.y + particle.velocity.y); // new coord for particle

        if (!mesh_bound.isInside(new_coordinate)) { // particle will move outside of mesh
            particle.velocity.x = -particle.velocity.x; // mirror velocity and dont change coordinate
            particle.velocity.y = -particle.velocity.y;
        } else {
            particle.coordinate = new_coordinate; // set new coordinate
        }
    }
}

void Cell::removeLostParticles(ParticleList &lost) {
    for (ParticleList::iterator it = particles.begin(); it != particles.end();) {
        const Particle &particle = *it;
        if (!isInside(particle)) { // particle moved outside of cell
            lost.push_back(particle); // add to lost
            it = particles.erase(it); // erase particle
        } else
            it++;
    }
}
