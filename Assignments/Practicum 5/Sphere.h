#ifndef SPHERE_H
#define SPHERE_H

#include "GeometricObject.h"
#include <cmath>

template <typename T>
class Sphere : public GeometricObject<T> {
private:
    T radius;

public:
    Sphere(T r) : radius(r) {}

    T perimeter() const override {
        return 0; // Not applicable for 3D shapes
    }

    T area() const override {
        return 4 * M_PI * radius * radius;
    }

    T volume() const override {
        return (4.0 / 3.0) * M_PI * radius * radius * radius;
    }

    T surfaceArea() const override {
        return 4 * M_PI * radius * radius;
    }
};

#endif
