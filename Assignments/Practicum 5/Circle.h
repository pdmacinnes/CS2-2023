#ifndef CIRCLE_H
#define CIRCLE_H

#include "GeometricObject.h"
#include <cmath>

template <typename T>
class Circle : public GeometricObject<T> {
private:
    T radius;

public:
    Circle(T r) : radius(r) {}

    T perimeter() const override {
        return 2 * M_PI * radius;
    }

    T area() const override {
        return M_PI * radius * radius;
    }

    T volume() const override {
        return 0; // Not applicable for 2D shapes
    }

    T surfaceArea() const override {
        return 0; // Not applicable for 2D shapes
    }
};

#endif
