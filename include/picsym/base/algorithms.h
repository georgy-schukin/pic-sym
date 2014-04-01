#pragma once

namespace picsym {

namespace alg {

template<class T, class ForwardIt, class Function>
T max(ForwardIt first, ForwardIt last, T fail, Function fn) {
    if (first == last) {
        return fail;
    }
    ForwardIt max = first;
    T max_val = fn(*max);
    for (++first; first != last; ++first) {
        const T val = fn(*first);
        if (val > max_val) {
            max = first;
            max_val = val;
        }
    }
    return max_val;
}

template<class T, class ForwardIt, class Function>
T sum(ForwardIt first, ForwardIt last, T init, Function fn) {
    for (; first != last; ++first) {
        init += fn(*first);
    }
    return init;
}

}

}
