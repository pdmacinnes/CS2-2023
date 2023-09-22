#ifndef SQUARE_H
#define SQUARE_H

#include "GeometricObject.h"

template <typename T>
class Square : public GeometricObject<T> {
protected: // Change 'private' to 'protected'
    T side;

public:
    Square(T s) : side(s) {}

    T perimeter() const override {
        return 4 * side;
    }

    T area() const override {
        return side * side;
    }

    T volume() const override {
        return 0; // Not applicable for 2D shapes
    }

    T surfaceArea() const override {
        return 0; // Not applicable for 2D shapes
    }
};

#endif
