#include "picsym/base/globalenv.h"

namespace picsym {

GlobalEnvironment& GlobalEnvironment::get() {
    static GlobalEnvironment env;
    return env;
}

}


