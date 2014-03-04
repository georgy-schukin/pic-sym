#pragma once

#ifndef Q_MOC_RUN
#include <boost/ptr_container/ptr_vector.hpp>
#endif

#include <QGraphicsScene>
#include <cstddef>
#include <vector>
#include "nodethread.h"
#include "cellmesh2d.h"

namespace picsym {

class ParallelMachine {
private:
    typedef boost::ptr_vector<NodeThread> NodeThreadArray;

private:    
    NodeThreadArray threads;

public:
    ParallelMachine() {}    
    ~ParallelMachine() {
        stop();
    }

    void start(const size_t& num_of_nodes, const CellMesh2D& mesh);
    void stop();

    void draw(QGraphicsScene& scene);
};

}
