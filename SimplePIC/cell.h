#pragma once

#include "rect2d.h"
#include "particle.h"
#include <list>

typedef std::list<Particle> ParticleList;

/**
  * Cell has position in space and contains particles
  */
class Cell {
public:
    Rect2D bound;
    ParticleList particles;

public:
    Cell() {}
    ~Cell() {}

    void addParticle(const Particle &p) {
        particles.push_back(p);
    }

    void addParticles(const ParticleList &p) {
        particles.insert(particles.end(), p.begin(), p.end());
    }

    bool isInside(const Particle &particle) {
        return bound.isInside(particle.coordinate);
    }

    void compute(const Rect2D &mesh_bound) {
        for (Particle &particle : particles) {

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

    void removeLostParticles(ParticleList &lost) {
        for (ParticleList::iterator it = particles.begin(); it != particles.end();) {
            const Particle &particle = *it;
            if (!isInside(particle)) { // particle moved outside of cell
                lost.push_back(particle); // add to lost
                it = particles.erase(it); // erase particle
            } else
                it++;
        }
    }
};
