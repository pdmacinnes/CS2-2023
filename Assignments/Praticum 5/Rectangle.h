#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GeometricObject.h"

template <typename T>
class Rectangle : public GeometricObject<T> {
private:
    T width;
    T height;

public:
    Rectangle(T w, T h) : width(w), height(h) {}

    T perimeter() const override {
        return 2 * (width + height);
    }

    T area() const override {
        return width * height;
    }

    T volume() const override {
        return 0; // Not applicable for 2D shapes
    }

    T surfaceArea() const override {
        return 0; // Not applicable for 2D shapes
    }
};

#endif
