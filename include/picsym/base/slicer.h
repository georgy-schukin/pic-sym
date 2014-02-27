#pragma once

#include <vector>
#include <cstddef>

namespace picsym {

/**
 * @brief Slice some length equally on num parts
 */
class Slicer {
public:
    static void slice(const size_t& length, const size_t& num, std::vector<size_t>& result);
};

}
