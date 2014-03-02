#pragma once

#ifndef Q_MOC_RUN
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#endif


namespace picsym {

/**
 * @brief Activity that runs in separate thread
 */
class ThreadActivity
{
private:
    boost::thread *thread;
    bool is_working;

protected:
    virtual void threadFunction() = 0;

public:
    ThreadActivity() : thread(0), is_working(false) {}
    ~ThreadActivity() {
        stop();
    }

    const bool& isWorking() const {
        return is_working;
    }

    void start();
    void stop();
};

}
