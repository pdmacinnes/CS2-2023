//
//  RectangleException.hpp
//  Recitation Week 7
//
//  Created by Antoun, Sherine on 10/3/23.
//

#ifndef RectangleException_hpp
#define RectangleException_hpp

#include "ShapeException.hpp"

class RectangleException : public ShapeException {
public:
    RectangleException(const std::string& message);
};

#endif // RECTANGLEEXCEPTION_HPP
