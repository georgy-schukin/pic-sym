#pragma once

#ifndef Q_MOC_RUN
#include <boost/thread/mutex.hpp>
#endif

#include "base/inode.h"
#include "base/threadactivity.h"
#include <map>

namespace picsym {

class NodeThread : public INode, public ThreadActivity
{
private:
    mutable boost::mutex mutex;    

private:
    CellRange my_cells;

private:
    size_t id;
    std::map<size_t, INode*> neighbours;
    std::map<size_t, size_t> curr_load;

private:
    void threadFunction();

public:
    NodeThread(const size_t& i) : id(i) {}
    NodeThread(const size_t &i, const CellRange& cells) : id(i) {
        sendCells(id, cells);
    }  
    ~NodeThread() {}

    const size_t& getId() const {
        return id;
    }

    void addNeighbour(const size_t& neigh_id, INode *neighbour);
    void sendLoadInfo(const size_t& src_id, const size_t& load);
    void sendCells(const size_t& src_id, const CellRange& cells);

    size_t getCurrentLoad() const;
};

}
