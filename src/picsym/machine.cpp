#include "picsym/machine.h"
#include "picsym/slicer.h"

namespace picsym {

void Machine::init(const size_t& num_of_nodes, const Mesh2D& mesh) {
    std::vector<size_t> part_sizes;

    Slicer::slice(mesh.getNumOfCells(), num_of_nodes, part_sizes);

    nodes.clear();
    size_t start = 0;
    for (size_t node = 0; node < num_of_nodes; node++) {
        nodes.push_back(Node(node, mesh, start, start + part_sizes[node]));
        start += part_sizes[node];
    }
}

void Machine::draw(QGraphicsScene &scene) {

}

}
