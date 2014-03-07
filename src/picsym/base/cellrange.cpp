#include "picsym/base/cellrange.h"
//#include "picsym/base/hilbert.h"

namespace picsym {

size_t CellRange::getFrontId() const {
    return (isEmpty() ? 0 : front().getId());
}

size_t CellRange::getBackId() const {
    return (isEmpty() ? 0 : back().getId());
}

void CellRange::add(const Cell& cell) {
    if (isEmpty())
        cells.push_back(cell);
    else {
        const size_t id = cell.getId();
        if (id < cells.front().getId())
            cells.push_front(cell); // push to left
        else if (id > cells.back().getId())
            cells.push_back(cell); // push to right
        else { // id is in the range
            for (std::list<Cell>::iterator it = cells.begin(); it != cells.end(); it++) {
                if (id == it->getId()) { // there is a cell with simular id
                    it->merge(cell);
                    break;
                } else if (id < it->getId()) {
                    cells.insert(it, cell);
                    break;
                }
            }
        }
    }
}

void CellRange::add(const CellRange& cell_range) {
    for (const_iterator it = cell_range.begin(); it != cell_range.end(); it++)
        add(*it);
}

Cell CellRange::removeFromFront() {
    Cell cell = cells.front();
    cells.pop_front();
    return cell;
}

Cell CellRange::removeFromBack() {
    Cell cell = cells.back();
    cells.pop_back();
    return cell;
}

Cell CellRange::remove(const bool& from_back) {
    return (from_back) ? removeFromBack() : removeFromFront();
}

Cell CellRange::splitFront(const size_t& particles_to_take) {
    return cells.front().split(particles_to_take);
}

Cell CellRange::splitBack(const size_t& particles_to_take) {
    return cells.back().split(particles_to_take);
}

Cell CellRange::split(const size_t& particles_to_take, const bool& from_back) {
    return (from_back) ? splitBack(particles_to_take) : splitFront(particles_to_take);
}

Cell CellRange::split(const bool& from_back) {
    return (from_back) ? cells.back().split() : cells.front().split();
}

}
