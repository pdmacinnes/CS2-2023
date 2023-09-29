#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H

template <typename T>
class GeometricObject {
public:
    virtual T perimeter() const = 0; // Pure virtual function
    virtual T area() const = 0;     // Pure virtual function
    virtual T volume() const = 0;   // Pure virtual function
    virtual T surfaceArea() const = 0; // Pure virtual function
};

#endif
