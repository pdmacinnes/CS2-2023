#include <iostream>
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
#include "Cube.h"
#include "RectangularBox.h"
#include "Sphere.h"

int main() {
    Rectangle<double> rectangle(5.0, 4.0);
    Circle<double> circle(3.0);
    Square<double> square(4.0);
    Cube<double> cube(3.0);
    RectangularBox<double> box(4.0, 5.0, 6.0);
    Sphere<double> sphere(3.0);

    std::cout << "Rectangle Perimeter: " << rectangle.perimeter() << std::endl;
    std::cout << "Rectangle Area: " << rectangle.area() << std::endl;
    std::cout << "Circle Perimeter: " << circle.perimeter() << std::endl;
    std::cout << "Circle Area: " << circle.area() << std::endl;
    std::cout << "Square Perimeter: " << square.perimeter() << std::endl;
    std::cout << "Square Area: " << square.area() << std::endl;
    std::cout << "Cube Volume: " << cube.volume() << std::endl;
    std::cout << "Cube Surface Area: " << cube.surfaceArea() << std::endl;
    std::cout << "Rectangular Box Volume: " << box.volume() << std::endl;
    std::cout << "Rectangular Box Surface Area: " << box.surfaceArea() << std::endl;
    std::cout << "Sphere Volume: " << sphere.volume() << std::endl;
    std::cout << "Sphere Surface Area: " << sphere.surfaceArea() << std::endl;

    return 0;
}
