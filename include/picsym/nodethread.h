#pragma once

#include "inode.h"
#include <boost/thread.hpp>

namespace picsym {

class NodeThread : public INode
{
private:
    boost::thread thread;

private:
    void ThreadFunc();

public:
    NodeThread() {}
    ~NodeThread() {}

    void start();
    void stop();

};

}
