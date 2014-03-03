#include "picsym/base/threadactivity.h"

namespace picsym {

void ThreadActivity::start() {
    stop();
    is_working = true;
    thread.reset(new boost::thread(&ThreadActivity::threadFunction, this));
}

void ThreadActivity::stop() {
    is_working = false;
    if (thread.get()) {
        thread->join();
        thread.reset(0);
    }
}

}
