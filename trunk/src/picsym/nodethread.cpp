#include "picsym/nodethread.h"
#include "picsym/base/hilbert.h"
#include "picsym/base/globalenv.h"
#include "picsym/base/algorithms.h"

namespace picsym {

void NodeThread::threadFunction() {
    while (isWorking()) {
        update();
        compute();
        processIncoming();
        balance();
    }
}

void NodeThread::compute() {
    for (CellRange::iterator it = my_cells.begin(); it != my_cells.end(); it++) {
        it->compute();
    //    boost::this_thread::sleep(boost::posix_time::milliseconds(5)); // work imitation
    }
    boost::this_thread::sleep(boost::posix_time::milliseconds(500)); // work imitation
}

void NodeThread::balance() {
    //boost::unique_lock<boost::mutex> lock(mutex);

    const LoadType my_load = getCurrentLoad();
    const size_t max_node = getMaxLoadedNode();
    const LoadType max_node_load = neighbours_load[max_node];

    if ((max_node_load > my_load) /*&& (100*(max_node_load - my_load)/max_node_load >= 5)*/) {
        neighbours[max_node]->requestCells(id, (max_node_load - my_load)/2);
    }
}

void NodeThread::update() {
    //boost::unique_lock<boost::mutex> lock(mutex);
    const LoadType curr_load = getCurrentLoad();
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

void NodeThread::sendLoadInfo(const size_t& src_id, const LoadType& load) {    
    incoming_load_info.push(LoadPair(src_id, load));
}

void NodeThread::requestCells(const size_t& src_id, const LoadType& load) {    
    incoming_cell_requests.push(LoadPair(src_id, load));
}

void NodeThread::sendCells(const size_t& src_id, const CellRange& cells) {    
    incoming_cells.push(cells);
}

void NodeThread::processIncomingLoad() {
    incoming_load_info.popAll(boost::bind(&NodeThread::setLoadInfo, this, _1));
}

void NodeThread::processIncomingRequests() {
    incoming_cell_requests.popAll(boost::bind(&NodeThread::processRequest, this, _1));
}

void NodeThread::processIncomingCells() {
    incoming_cells.popAll(boost::bind(&NodeThread::addCells, this, _1));
}

void NodeThread::processRequest(const LoadPair &p) {
    const size_t& src_id = p.first;
    const LoadType& load = p.second;
    const LoadType current_load = getCurrentLoad();
    const LoadType load_to_give = (current_load/2 > load) ? load : current_load/2; // give no more than a half of the current load
    neighbours[src_id]->sendCells(id, takeCells(load_to_give, (src_id > id)));
}

void NodeThread::setLoadInfo(const LoadPair &p) {
    const size_t& src_id = p.first;
    const LoadType& load = p.second;
    neighbours_load[src_id] = load;
}

void NodeThread::addCells(const CellRange &range) {
    boost::unique_lock<boost::mutex> lock(mutex);
    my_cells.add(range);
}

CellRange NodeThread::takeCells(const LoadType& load, const bool& from_back) {
    boost::unique_lock<boost::mutex> lock(mutex);
    LoadType accumulated_load = 0;
    CellRange cells_to_give;    
    while ((accumulated_load < load) && !my_cells.isEmpty()) {
        const LoadType next_load = (from_back) ? my_cells.back().getLoad() : my_cells.front().getLoad();
        if (accumulated_load + next_load > load) { // too much load to take
            Cell new_cell = my_cells.split(load - accumulated_load, from_back); // split this cell
            cells_to_give.add(new_cell);
            accumulated_load += new_cell.getLoad();
        } else {
            cells_to_give.add(my_cells.remove(from_back)); // take this cell
            accumulated_load += next_load;
        }
    }
    return cells_to_give;
}

void NodeThread::drawCells(QGraphicsScene &scene, const QColor &base_color, const size_t &mesh_size, const size_t &num) const {
    boost::unique_lock<boost::mutex> lock(mutex);

    const float max = (num > 0) ? float(num) : 1.0;
    QPen pen(base_color);

    for (CellRange::const_iterator it = my_cells.begin(); it != my_cells.end(); it++) {
        const Coord2D<size_t> coord = Hilbert::distanceToCoord(it->getId(), mesh_size);
        const float scale = float(it->getNumOfParticles())/max;
        const QColor cell_color(base_color.red()*scale, base_color.green()*scale, base_color.blue()*scale, base_color.alpha()*scale);
        scene.addRect(QRectF(coord.getX()*10, coord.getY()*10, 8, 8), pen, QBrush(cell_color));
    }
}

size_t NodeThread::getMaxLoadedNode() {
    size_t id_max = neighbours_load.begin()->first;
    for (NeighLoadMap::iterator it = neighbours_load.begin(); it != neighbours_load.end(); it++)
        if (neighbours_load.at(id_max) < it->second)
            id_max = it->first;
    return id_max;
}

LoadType _getLoad(const Cell& c) {
    return c.getLoad();
}

size_t _getNumOfParticles(const Cell& c) {
    return c.getNumOfParticles();
}

LoadType NodeThread::getCurrentLoad() const {
    boost::unique_lock<boost::mutex> lock(mutex);
    return alg::sum<LoadType>(my_cells.begin(), my_cells.end(), 0, _getLoad);
}

size_t NodeThread::getMaxNumOfParticlesInCell() const {
    boost::unique_lock<boost::mutex> lock(mutex);
    return alg::max<size_t>(my_cells.begin(), my_cells.end(), 0, _getNumOfParticles);
}

size_t NodeThread::getCurrentNumOfParticles() const {
    boost::unique_lock<boost::mutex> lock(mutex);
    return alg::sum<size_t>(my_cells.begin(), my_cells.end(), 0, _getNumOfParticles);
}

size_t NodeThread::getCurrentNumOfCells() const {
    boost::unique_lock<boost::mutex> lock(mutex);
    return my_cells.getSize();
}

void NodeThread::getStat(NodeStat &stat) {
    stat.load = getCurrentLoad();
    stat.num_of_cells = getCurrentNumOfCells();
    stat.num_of_particles = getCurrentNumOfParticles();
}

}
