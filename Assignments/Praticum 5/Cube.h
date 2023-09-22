#ifndef CUBE_H
#define CUBE_H

#include "Square.h"

template <typename T>
class Cube : public Square<T> {
public:
    Cube(T s) : Square<T>(s) {}

    T volume() const override {
        return this->side * this->side * this->side;
    }

    T surfaceArea() const override {
        return 6 * this->side * this->side;
    }
};

#endif
