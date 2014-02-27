#pragma once

#include <QGraphicsScene>
#include <cstddef>
#include <vector>
#include "nodethread.h"
#include "cellmesh2d.h"

namespace picsym {

class ParallelMachine {
private:    
    std::vector<NodeThread> threads;

public:
    ParallelMachine() {}
    ParallelMachine(const size_t& num_of_nodes, const CellMesh2D& mesh) {
        init(num_of_nodes, mesh);
    }

    ~ParallelMachine() {}

    void init(const size_t& num_of_nodes, const CellMesh2D& mesh);
    void start();
    void stop();

    void draw(QGraphicsScene& scene);
};

}
