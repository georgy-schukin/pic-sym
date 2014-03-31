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
    size_t mesh_size;
    size_t total_num_of_cells;
    size_t total_num_of_particles;

private:
    //LoadType getMaxCellLoad() const;
    size_t getMaxNumOfParticlesInCell() const;

public:
    ParallelMachine() {}    
    ~ParallelMachine() {
        stop();
    }

    void start(const size_t& num_of_nodes, const CellMesh2D& mesh);
    void stop();

    void drawLoad(QGraphicsScene& scene);
    void drawCells(QGraphicsScene& scene);
};

}
