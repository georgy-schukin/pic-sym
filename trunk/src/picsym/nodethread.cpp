#include "picsym/nodethread.h"

namespace picsym {

void NodeThread::ThreadFunc() {

}

void NodeThread::start() {

}

void NodeThread::stop() {

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
    if (src_id >= id) { // get cells from right
        my_cells.addToEnd(cells);
    } else { // get cells from left
        my_cells.addToStart(cells);
    }
}

}
