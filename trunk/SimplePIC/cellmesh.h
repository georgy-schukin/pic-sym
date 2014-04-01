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

public:
    CellMesh(const int &w, const int &h, const Rect2D &b) : width(w), height(h), bound(b) {

        cells.resize(width*height); // create array of cells

        cell_width = bound.width()/width; // cell size by X
        cell_height = bound.height()/height; // cell size by Y

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                const double cx = bound.left + j*cell_width; // cell left coord by X
                const double cy = bound.top - i*cell_height; // cell top coord by Y (go from top to bottom by i)
                cells[i*width + j].bound = Rect2D(cx, cx + cell_width, cy - cell_height, cy); // set cell's bound
            }
    }
    ~CellMesh() {}

    iterator begin() {
        return cells.begin();
    }

    iterator end() {
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

    // Get cell index by particle coord
    int getCellIndex(const Vector2D &coord) {
        const int ix = (coord.x - bound.right < 1e-9) ? width - 1 : int(floor((coord.x - bound.left) / cell_width)); // get cell indices for coord
        const int iy = (coord.y - bound.bottom < 1e-9) ? height - 1 : int(floor((bound.top - coord.y) / cell_height));

        if ((ix >= 0) && (ix < width) && (iy >=0) && (iy < height)) { // particle is inside of mesh
            return iy*width + ix; // get cell index
        } else
            return -1;
    }

    int getNumOfParticles() const {
        int num = 0;
        for (const Cell &cell : cells)
            num += cell.particles.size();
        return num;
    }
};
