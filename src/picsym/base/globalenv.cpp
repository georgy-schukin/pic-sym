#include "picsym/base/globalenv.h"

namespace picsym {

GlobalEnvironment global_environment;

const GlobalEnvironment& getGlobalEnvironment() {
    return global_environment;
}

void setGlobalEnvironment(const GlobalEnvironment& env) {
    global_environment = env;
}

}


