#pragma once

#include "base/inode.h"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace picsym {

class NodeThread : public INode
{
private:
    boost::thread thread;
    boost::mutex mutex;

private:
    void ThreadFunc();

public:
    NodeThread() {}
    ~NodeThread() {}

    void start();
    void stop();

    void addNeighbour(const size_t& id, INode *neighbour);
    void sendLoadInfo(const size_t& src_id, const size_t& load);
    void sendCells(const size_t& src_id, const Array<Cell>& cells);

};

}
