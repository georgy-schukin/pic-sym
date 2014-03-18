#pragma once

namespace picsym {

template <class T>
class Rect2D
{
private:
    T left;
    T right;
    T top;
    T bottom;

public:
    Rect2D() : left(0), right(0), top(0), bottom(0) {}
    Rect2D(const T& l, const T& r, const T& t, const T& b) : left(l), right(r), top(t), bottom(b) {}
    Rect2D(const Rect2D<T>& r) : left(r.left), right(r.right), top(r.top), bottom(r.bottom) {}
    ~Rect2D() {}

    const T& getLeft() const {
        return left;
    }

    const T& getRight() const {
        return right;
    }

    const T& getTop() const {
        return top;
    }

    const T& getBottom() const {
        return bottom;
    }

    T width() const {
        return (right > left) ? right - left : left - right;
    }

    T height() const {
        return (top > bottom) ? top - bottom : bottom - top;
    }
};

}
