#pragma once

#include "list.h"
#include "cellrange.h"

namespace picsym {

/**
 * @brief Node interface
 */
class INode {
public:
    struct NodeStat {
        LoadType load;
        size_t num_of_cells;
        size_t num_of_particles;
    };

public:
    virtual size_t getId() const = 0;
    virtual void addNeighbour(INode *neighbour) = 0;
    virtual void sendLoadInfo(const size_t& src_id, const LoadType& load) = 0;
    virtual void requestCells(const size_t& src_id, const LoadType& load) = 0;
    virtual void sendCells(const size_t& src_id, const CellRange& cells) = 0;    
    virtual void getStat(NodeStat& stat) = 0;
};

}
