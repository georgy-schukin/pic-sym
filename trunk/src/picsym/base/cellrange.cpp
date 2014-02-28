#include "picsym/base/cellrange.h"
//#include "picsym/base/hilbert.h"

namespace picsym {

/*void CellRange::initByHilbert(const CellMesh2D& mesh, const size_t& start, const size_t& end) {
    range_start = start;
    //range_end = end;

    //cells.resize(end - start);

    const size_t& mesh_size = mesh.getWidth();

    for (size_t dist = Range_start; dist < Range_end; dist++) {
        size_t x = 0, y = 0;
        Hilbert::distanceToCoord(dist, mesh_size, x, y);     
        //cells.at(dist - Range_start) = mesh(y, x);
    }
}*/

size_t CellRange::getStartId() const {
    return (isEmpty() ? 0 : front().getId());
}

size_t CellRange::getEndId() const {
    return (isEmpty() ? 0 : back().getId());
}

void CellRange::addToStart(const Cell& cell) {
    if (isEmpty())
        cells.push_front(cell);
    else {
        if (cells.front().getId() == cell.getId())
            cells.front().addParticles(cell.getNumOfParticles());
        else
            cells.push_front(cell);
    }
}

void CellRange::addToStart(const CellRange& cell_range) {
    for (const_reverse_iterator it = cell_range.rbegin(); it != cell_range.rend(); it++)
        addToStart(*it);
}

void CellRange::addToEnd(const Cell& cell) {
    if (isEmpty())
        cells.push_back(cell);
    else {
        if (cells.back().getId() == cell.getId())
            cells.back().addParticles(cell.getNumOfParticles());
        else
            cells.push_back(cell);
    }
}

void CellRange::addToEnd(const CellRange& cell_range) {
    for (const_iterator it = cell_range.begin(); it != cell_range.end(); it++)
        addToEnd(*it);
}

Cell CellRange::removeFromStart() {
    Cell cell = cells.front();
    cells.pop_front();
    return cell;
}

Cell CellRange::removeFromEnd() {
    Cell cell = cells.back();
    cells.pop_back();
    return cell;
}

Cell CellRange::separateStart(const size_t& particles_to_take) {
    Cell cell = cells.front();
    cell.setNumOfParticles(particles_to_take);
    cells.front().removeParticles(particles_to_take);
    return cell;
}

Cell CellRange::separateEnd(const size_t& particles_to_take) {
    Cell cell = cells.back();
    cell.setNumOfParticles(particles_to_take);
    cells.back().removeParticles(particles_to_take);
    return cell;
}

}
