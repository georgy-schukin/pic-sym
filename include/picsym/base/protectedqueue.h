#pragma once

#ifndef Q_MOC_RUN
#include <boost/thread/mutex.hpp>
#endif
#include <queue>

namespace picsym {

template <class T>
class ProtectedQueue
{
private:
    std::queue<T> queue;
    boost::mutex mutex;

public:
    ProtectedQueue() {}
    ~ProtectedQueue() {}

    void push(const T& elem) {
        boost::unique_lock<boost::mutex> lock(mutex);
        queue.push(elem);
    }

    template<class Function>
    void popAll(Function fn) {
        boost::unique_lock<boost::mutex> lock(mutex);
        while (!queue.empty()) {
            fn(queue.front());
            queue.pop();
        }
    }
};

}
