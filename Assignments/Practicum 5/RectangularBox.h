#ifndef RECTANGULARBOX_H
#define RECTANGULARBOX_H

#include "GeometricObject.h"

template <typename T>
class RectangularBox : public GeometricObject<T> {
private:
    T width;
    T height;
    T depth;

public:
    RectangularBox(T w, T h, T d) : width(w), height(h), depth(d) {}

    T perimeter() const override {
        return 0; // Not applicable for 3D shapes
    }

    T area() const override {
        return 0; // Not applicable for 3D shapes
    }

    T volume() const override {
        return width * height * depth;
    }

    T surfaceArea() const override {
        return 2 * (width * height + height * depth + depth * width);
    }
};

#endif
