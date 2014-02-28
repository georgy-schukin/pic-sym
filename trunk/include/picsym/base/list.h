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
    typedef typename std::list<T>::reverse_iterator reverse_iterator;
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

    reverse_iterator rbegin() const {
        return data.rbegin();
    }

    reverse_iterator rend() const {
        return data.rend();
    }

    void pushToBack(const T& elem) {
        data.push_back(elem);
    }

    void pushToFront(const T& elem) {
        data.push_front(elem);
    }

    void pushToBack(iterator start, iterator end) {
        data.insert(data.end(), start, end);
    }

    void pushToFront(iterator start, iterator end) {
        data.insert(data.begin(), start, end);
    }

    T popFromBack() {
        T elem = data.back();
        data.pop_back();
        return elem;
    }

    T popFromFront() {
        T elem = data.front();
        data.pop_front();
        return elem;
    }

    const T& back() const {
        return data.back();
    }

    const T& front() const {
        return data.front();
    }

    bool isEmpty() const {
        return data.empty();
    }
};

}
