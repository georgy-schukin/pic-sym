#pragma once

#include "cell.h"
#include <vector>
#include <cmath>

/**
  * 2D array of cells
  */
class CellMesh
{
private:
    std::vector<Cell> cells;
    int width; // num of cells by X
    int height; // num of cells by Y
    double cell_width;
    double cell_height;
    Rect2D bound; // coordinates of mesh in space

public:
    typedef std::vector<Cell>::iterator iterator;
    typedef std::vector<Cell>::const_iterator const_iterator;

public:
    CellMesh(const int &w, const int &h, const Rect2D &b) {
        init(w, h, b);
    }
    ~CellMesh() {}

    iterator begin() {
        return cells.begin();
    }

    iterator end() {
        return cells.end();
    }

    const_iterator begin() const {
        return cells.begin();
    }

    const_iterator end() const {
        return cells.end();
    }

    Cell& at(const int &index) {
        return cells.at(index);
    }

    const int& getWidth() const {
        return width;
    }

    const int& getHeight() const {
        return height;
    }

    const Rect2D& getBound() const {
        return bound;
    }

    void init(const int &w, const int &h, const Rect2D &b);
    void addParticleInCell(const Particle &particle);
    int getCellIndex(const Vector2D &coord) const;
    int getNumOfParticles() const;
};
