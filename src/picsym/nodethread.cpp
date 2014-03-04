#include "picsym/nodethread.h"

namespace picsym {

void NodeThread::threadFunction() {
    while (isWorking()) {

        update();

        boost::this_thread::sleep(boost::posix_time::milliseconds(500)); // work imitation

        processIncoming();

        balance();
    }
}

void NodeThread::balance() {
    boost::unique_lock<boost::mutex> lock(mutex);

    const size_t my_load = getCurrentLoad();
    const size_t max_node = getMaxLoadedNode();
    const size_t max_node_load = neighbours_load[max_node];

    if ((max_node_load > my_load) /*&& (100*(max_node_load - my_load)/max_node_load >= 5)*/) {
        neighbours[max_node]->requestCells(id, (max_node_load - my_load)/2);
    }
}

void NodeThread::update() {
    boost::unique_lock<boost::mutex> lock(mutex);

    const size_t curr_load = getCurrentLoad();
    for (NeighNodeMap::iterator it = neighbours.begin(); it != neighbours.end(); it++)
        it->second->sendLoadInfo(id, curr_load);
}

void NodeThread::processIncoming() {
    processIncomingLoad();
    processIncomingCells();
    processIncomingRequests();
}

void NodeThread::addNeighbour(INode *neighbour) {
    const size_t neigh_id = neighbour->getId();
    neighbours[neigh_id] = neighbour;
    neighbours_load[neigh_id] = 0;
}

void NodeThread::sendLoadInfo(const size_t& src_id, const size_t& load) {
    boost::unique_lock<boost::mutex> lock(lmutex);
    incoming_load_info.push(UIntPair(src_id, load));
}

void NodeThread::sendCells(const size_t& src_id, const CellRange& cells) {
    boost::unique_lock<boost::mutex> lock(cmutex);
    incoming_cells.push(cells);
}

void NodeThread::requestCells(const size_t& src_id, const size_t& load) {
    boost::unique_lock<boost::mutex> lock(cmutex);
    incoming_cell_requests.push(UIntPair(src_id, load));
}

void NodeThread::processIncomingLoad() {
    boost::unique_lock<boost::mutex> lock(lmutex);

    while (!incoming_load_info.empty()) {
        const UIntPair& p = incoming_load_info.front();
        neighbours_load[p.first] = p.second;
        incoming_load_info.pop();
    }
}

void NodeThread::processIncomingRequests() {
    boost::unique_lock<boost::mutex> lock(rmutex);

    while (!incoming_cell_requests.empty()) {
        const UIntPair& p = incoming_cell_requests.front();
        processRequest(p.first, p.second);
        incoming_cell_requests.pop();
    }
}

void NodeThread::processIncomingCells() {
    boost::unique_lock<boost::mutex> lock(cmutex);

    while (!incoming_cells.empty()) {
        my_cells.add(incoming_cells.front());
        incoming_cells.pop();
    }
}

void NodeThread::processRequest(const size_t &src_id, const size_t &load) {
    boost::unique_lock<boost::mutex> lock(mutex);

    const size_t current_load = getCurrentLoad();
    const size_t load_to_give = (current_load/2 > load) ? load : current_load/2; // take no more than half of current load
    neighbours[src_id]->sendCells(id, takeCells(load_to_give, (src_id > id)));
}

size_t NodeThread::getCurrentLoad() const {    
    size_t load = 0;
    for (CellRange::const_iterator it = my_cells.begin(); it != my_cells.end(); it++)
        load += it->getNumOfParticles();
    return load;
}

CellRange NodeThread::takeCells(const size_t& load, const bool& from_back) {
    size_t accumulated_load = 0;
    CellRange cells_to_give;

    while ((accumulated_load < load) && !my_cells.isEmpty()) {
        const size_t next_part = (from_back) ? my_cells.back().getNumOfParticles() : my_cells.front().getNumOfParticles();
        if (accumulated_load + next_part > load) { // next cell contains too many particles
            cells_to_give.add(my_cells.split(load - accumulated_load, from_back)); // split this cell
            accumulated_load = load;
        } else {
            cells_to_give.add(my_cells.remove(from_back)); // take next cell
            accumulated_load += next_part;
        }
    }
    return cells_to_give;
}

size_t NodeThread::getMaxLoadedNode() {
    size_t max = neighbours_load.begin()->first;
    for (NeighLoadMap::iterator it = neighbours_load.begin(); it != neighbours_load.end(); it++)
        if (neighbours_load[max] < it->second)
            max = it->first;
    return max;
}


}
