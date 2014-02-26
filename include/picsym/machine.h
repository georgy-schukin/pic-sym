#pragma once

#include <QGraphicsScene>
#include <cstddef>
#include <vector>
#include "picsym/node.h"

namespace picsym {

class Machine {
private:    
    std::vector<Node> nodes;

public:
    Machine() {}
    Machine(const size_t& num_of_nodes, const Mesh2D& mesh) {
        init(num_of_nodes, mesh);
    }

    ~Machine() {}

    void init(const size_t& num_of_nodes, const Mesh2D& mesh);
    void draw(QGraphicsScene& scene);
};

}
