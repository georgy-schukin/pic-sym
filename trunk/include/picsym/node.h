#pragma once

#include <cstddef>

namespace picsym {

class Node {
private:
    size_t start;
    size_t end;

public:
    Node() : start(0), end(0) {}
    ~Node() {}

    void setIndexStart(const size_t& s) {
        start = s;
    }

    void setIndexEnd(const size_t& e) {
        end = e;
    }

    const size_t& getIndexStart() const {
        return start;
    }

    const size_t& getIndexEnd() const {
        return end;
    }

};

}

