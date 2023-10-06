#include <iostream>
#include <fstream>
#include "ShapeException.hpp"
#include "CircleException.hpp"
#include "RectangleException.hpp"

// Custom log stream for redirecting cerr to a log file
class LogStream {
public:
    LogStream(const std::string& logFileName) : logFile(logFileName) {}

    template <typename T>
    LogStream& operator<<(const T& val) {
        logFile << val;
        return *this;
    }

    // Overload for manipulators like endl
    LogStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        manip(logFile);
        return *this;
    }

private:
    std::ofstream logFile;
};

LogStream log("error.log"); // Redirect cerr to log file

// Base class
class Shape {
public:
    virtual void draw() const {
        throw ShapeException("Cannot draw a generic shape.");
    }
};

// Derived class 1
class Circle : public Shape {
public:
    Circle(double radius) : radius(radius) {}

    void draw() const override {
        if (radius < 0) {
            throw CircleException("Circle radius cannot be negative.");
        }
        log << "Drawing a circle with radius " << radius << std::endl;
    }

private:
    double radius;
};

// Derived class 2
class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width(width), height(height) {}

    void draw() const override {
        if (width <= 0 || height <= 0) {
            throw RectangleException("Invalid rectangle dimensions.");
        }
        log << "Drawing a rectangle with dimensions " << width << "x" << height << std::endl;
    }

private:
    double width;
    double height;
};

int main() {
    try {
        Circle c1(5.0);
        Circle c2(-2.0);//after demo set as positive to trigger rectangle one
        Rectangle r1(4.0, 3.0);
        Rectangle r2(-1.0, 5.0);

        c1.draw();  // This is valid, it will print the circle
        c2.draw();  // This will throw a CircleException
        r1.draw();  // This is valid, it will print the rectangle
        r2.draw();  // This will throw a RectangleException
    }
    catch (const ShapeException& e) {
        log << "ShapeException: " << e.what() << std::endl;
    }
    catch (const CircleException& e) {
        log << "CircleException: " << e.what() << std::endl;
    }
    catch (const RectangleException& e) {
        log << "RectangleException: " << e.what() << std::endl;
    }
    catch (...) {
        log << "Caught an unknown exception." << std::endl;
    }

    return 0;
}
