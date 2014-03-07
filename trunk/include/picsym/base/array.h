#pragma once

#include <vector>
#include <cstddef>

namespace picsym {

/**
 * Array of data
 */
template <class T>
class Array
{
private:        
    typename std::vector<T> data;

public:
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

public:
    Array() {}
    Array(const size_t& size) {
        resize(size);
    }
    ~Array() {}

    size_t getSize() const {
        return data.size();
    }

    const T& operator[](const size_t& index) const {
        return data[index];
    }

    T& operator[](const size_t& index) {
        return data[index];
    }

    const T& at(const size_t& index) const {
        return data[index];
    }

    T& at(const size_t& index) {
        return data[index];
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
