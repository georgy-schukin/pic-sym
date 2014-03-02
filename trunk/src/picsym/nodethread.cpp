#include "picsym/nodethread.h"

namespace picsym {

void NodeThread::threadFunction() {
    while (isWorking()) {

    }
}

void NodeThread::addNeighbour(const size_t& neigh_id, INode *neighbour) {
    neighbours[neigh_id] = neighbour;
    curr_load[neigh_id] = 0;
}

void NodeThread::sendLoadInfo(const size_t& src_id, const size_t& load) {
    boost::unique_lock<boost::mutex> lock(mutex);
    curr_load[src_id] = load;
}

void NodeThread::sendCells(const size_t& src_id, const CellRange& cells) {
    boost::unique_lock<boost::mutex> lock(mutex);
    my_cells.add(cells);
}

size_t NodeThread::getCurrentLoad() const {
    boost::unique_lock<boost::mutex> lock(mutex);
    size_t load = 0;
    for (CellRange::const_iterator it = my_cells.begin(); it != my_cells.end(); it++)
        load += it->getNumOfParticles();
    return load;
}

}
