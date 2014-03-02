#include "picsym/base/threadactivity.h"

namespace picsym {

void ThreadActivity::start() {
    is_working = true;
    thread = new boost::thread(&ThreadActivity::threadFunction, this);
}

void ThreadActivity::stop() {
    is_working = false;
    if (thread) {
        thread->join();
        delete thread;
        thread = 0;
    }
}

}
