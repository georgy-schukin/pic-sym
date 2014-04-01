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

    void generateParticles(const int &max_num);
    void compute(const Rect2D &mesh_bound);
    void removeLostParticles(ParticleList &lost);
};
