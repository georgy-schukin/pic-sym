#pragma once

#include <vector>
#include <cstddef>

namespace picsym {

class Slicer {
public:
    static void slice(const size_t& length, const size_t& num, std::vector<size_t>& result);
};

}
