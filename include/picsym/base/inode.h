#pragma once

#include "array.h"

namespace picsym {

/**
 * @brief Node interface
 */
class INode {
public:
    virtual void addNeighbour(const size_t& id, INode *neighbour) = 0;
    virtual void sendLoadInfo(const size_t& src_id, const size_t& load) = 0;
    virtual void sendCells(const size_t& src_id, const Array<Cell>& cells) = 0;
};

}
