#include "picsym/slicer.h"

namespace picsym {

void Slicer::slice(const size_t& length, const size_t& num, std::vector<size_t>& result) {
    const size_t base_size = length / num;
    const size_t rest = length % num;

    for (size_t i = 0; i < num; i++) {
        const size_t slice_size = (i < rest) ? base_size : base_size + 1;
        result.push_back(slice_size);
    }
}

}
