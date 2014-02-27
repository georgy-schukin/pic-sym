#pragma once

#include <list>
#include <cstddef>

namespace picsym {

/**
 * List of data
 */
template <class T>
class List
{
private:
    typename std::list<T> data;

public:
    typedef typename std::list<T>::iterator iterator;
    typedef typename std::list<T>::const_iterator const_iterator;

public:
    List() {}
    List(const size_t& size) {
        resize(size);
    }
    ~List() {}

    size_t getSize() const {
        return data.size();
    }

    iterator begin() {
        return data.begin();
    }

    iterator end() {
        return data.end();
    }

    const_iterator begin() const {
        return data.begin();
    }

    const_iterator end() const {
        return data.end();
    }

    void resize(const size_t& size) {
        data.resize(size);
    }
};

}
