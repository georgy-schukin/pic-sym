#pragma once

#include <cstddef>

namespace picsym {

/**
 * @brief Transform from 2D integer coordinates to Hilbert curve integer distance and back
 */
class Hilbert
{
private:
    static void rotate(size_t& x, size_t& y, const size_t& mesh_size, const size_t& rx, const size_t& ry);

public:
    static size_t coordToDistance(const size_t& x, const size_t& y, const size_t& mesh_size);
    static void distanceToCoord(const size_t& dist, const size_t& mesh_size, size_t& x, size_t& y);
};

}
