#include "picsym/parallelmachine.h"
#include "picsym/base/slicer.h"

namespace picsym {

void ParallelMachine::start(const size_t& num_of_nodes, const CellMesh2D& mesh) {
    std::vector<size_t> part_sizes;

    Slicer::slice(mesh.getNumOfCells(), num_of_nodes, part_sizes);

    threads.clear();

    size_t start = 0;
    for (size_t node = 0; node < num_of_nodes; node++) {
        threads.push_back(new NodeThread(node, mesh.getRange(start, start + part_sizes[node])));
        start += part_sizes[node];
    }

    for (NodeThreadArray::iterator it = threads.begin(); it != threads.end(); it++)
        it->start();
}

void ParallelMachine::stop() {
    for (NodeThreadArray::iterator it = threads.begin(); it != threads.end(); it++)
        it->stop();
}

void ParallelMachine::draw(QGraphicsScene &scene) {

}

}