#include "picsym/parallelmachine.h"
#include "picsym/base/slicer.h"
#include <QGraphicsTextItem>
#include <numeric>

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

    for (size_t node = 0; node < threads.size(); node++) { // build linear topology
        if (node > 0)
            threads[node].addNeighbour(&threads[node - 1]); // left neighbour
        if (node < threads.size() - 1)
            threads[node].addNeighbour(&threads[node + 1]); // right neighbour
    }

    for (NodeThreadArray::iterator it = threads.begin(); it != threads.end(); it++)
        it->start();
}

void ParallelMachine::stop() {
    for (NodeThreadArray::iterator it = threads.begin(); it != threads.end(); it++)
        it->stop();
}

void ParallelMachine::draw(QGraphicsScene &scene) {
    std::vector<size_t> loads;
    for (NodeThreadArray::iterator it = threads.begin(); it != threads.end(); it++)
        loads.push_back(it->getCurrentLoad());

    const size_t min = *(std::min_element(loads.begin(), loads.end()));
    const size_t max = *(std::max_element(loads.begin(), loads.end()));

    QString text = "";
    for (size_t i = 0; i < loads.size(); i++) {
        text += QString("%1 : %2\n").arg(i).arg(loads[i]);
    }    
    text += QString("Total : %1\n").arg(std::accumulate(loads.begin(), loads.end(), 0));
    text += QString("Max diff : %1\n").arg(max - min);

    scene.addText(text);
}

}
