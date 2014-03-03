#include "picsym/nodethread.h"

namespace picsym {

void NodeThread::threadFunction() {
    while (isWorking()) {
        balance();
        boost::this_thread::sleep(boost::posix_time::milliseconds(500)); // work imitation
    }
}

void NodeThread::balance() {
    const size_t my_load = getCurrentLoad();
    for (NeighNodeMap::iterator it = neighbours.begin(); it != neighbours.end(); it++)
        it->second->sendLoadInfo(id, my_load);
}

bool NodeThread::isMinloaded(const size_t& load) {
    for (NeighLoadMap::const_iterator it = neighbours_load.begin(); it != neighbours_load.end(); it++)
        if (it->second <= load)
            return false;
    return true;
}

CellRange NodeThread::takeCells(const size_t& load, const bool& from_back) {
    size_t curr_load = 0;
    if (from_back) {

    }

}

void NodeThread::addNeighbour(const size_t& neigh_id, INode *neighbour) {
    neighbours[neigh_id] = neighbour;
    curr_load[neigh_id] = 0;
}

void NodeThread::sendLoadInfo(const size_t& src_id, const size_t& load) {
    boost::unique_lock<boost::mutex> lock(mutex);
    neighbours_load[src_id] = load;
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
