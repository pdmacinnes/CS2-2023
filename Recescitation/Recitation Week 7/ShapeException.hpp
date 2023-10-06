//
//  ShapeException.hpp
//  Recitation Week 7
//
//  Created by Antoun, Sherine on 10/3/23.
//

#ifndef SHAPEEXCEPTION_HPP
#define SHAPEEXCEPTION_HPP

#include <exception>
#include <string>

class ShapeException : public std::exception {
public:
    ShapeException(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string message;
};

#endif // SHAPEEXCEPTION_HPP
