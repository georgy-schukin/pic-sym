#pragma once

#ifndef Q_MOC_RUN
#include <boost/thread/mutex.hpp>
#endif
#include <queue>

namespace picsym {

template <class T1, class T2>
class ProtectedPairQueue
{
private:
    typedef typename std::pair<T1, T2> Pair;

private:
    std::queue<ProtectedPairQueue::Pair> queue;
    boost::mutex mutex;

public:
    ProtectedPairQueue() {}
    ~ProtectedPairQueue() {}

    void push(const T1& first, const T2& second) {
        boost::unique_lock<boost::mutex> lock(mutex);
        queue.push(ProtectedPairQueue::Pair(first, second));
    }

    template<class Function>
    void popAll(Function fn) {
        boost::unique_lock<boost::mutex> lock(mutex);
        while (!queue.empty()) {
            const ProtectedPairQueue::Pair& p = queue.front();
            fn(p.first, p.second);
            queue.pop();
        }
    }
};

}
