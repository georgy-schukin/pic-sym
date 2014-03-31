#pragma once

#include "list.h"
#include "cellrange.h"

namespace picsym {

/**
 * @brief Node interface
 */
class INode {
public:
    virtual const size_t& getId() const = 0;
    virtual void addNeighbour(INode *neighbour) = 0;
    virtual void sendLoadInfo(const size_t& src_id, const double& load) = 0;
    virtual void requestCells(const size_t& src_id, const double& load) = 0;
    virtual void sendCells(const size_t& src_id, const CellRange& cells) = 0;    
};

}
