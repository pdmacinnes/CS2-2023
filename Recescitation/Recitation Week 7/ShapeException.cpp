//
//  ShapeException.cpp
//  Recitation Week 7
//
//  Created by Antoun, Sherine on 10/3/23.
//
#include "ShapeException.hpp"

ShapeException::ShapeException(const std::string& message) : message(message) {}

const char* ShapeException::what() const noexcept {
    return message.c_str();
}
