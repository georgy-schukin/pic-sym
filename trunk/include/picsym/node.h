#pragma once

#include <cstddef>
#include "picsym/meshpart.h"

namespace picsym {

/**
 * @brief Node that contains part of a distributed mesh
 */
class Node {
private:
    size_t id;
    MeshPart mesh_part;

public:
    Node() : id(0) {}
    Node(const size_t& i) : id(i) {}
    Node(const size_t& i, const Mesh2D& mesh, const size_t& start, const size_t& end) : id(i), mesh_part(mesh, start, end) {}
    ~Node() {}

    const MeshPart& getMesh() const {
        return mesh_part;
    }
};

}
