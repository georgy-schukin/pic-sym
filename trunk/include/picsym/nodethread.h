#pragma once

#include "base/inode.h"
#include <map>

#ifndef Q_MOC_RUN
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#endif

namespace picsym {

class NodeThread : public INode
{
private:
    boost::thread thread;
    boost::mutex mutex;

private:
    CellRange my_cells;

private:
    size_t id;
    std::map<size_t, INode*> neighbours;
    std::map<size_t, size_t> curr_load;

private:
    void ThreadFunc();

public:
    NodeThread(const size_t& i) : id(i) {}
    ~NodeThread() {}

    void start();
    void stop();

    const size_t& getId() const {
        return id;
    }

    void addNeighbour(const size_t& neigh_id, INode *neighbour);
    void sendLoadInfo(const size_t& src_id, const size_t& load);
    void sendCells(const size_t& src_id, const CellRange& cells);
};

}
