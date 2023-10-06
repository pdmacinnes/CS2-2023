//
//  CircleException.hpp
//  Recitation Week 7
//
//  Created by Antoun, Sherine on 10/3/23.
//

#ifndef CircleException_hpp
#define CircleException_hpp


#include "ShapeException.hpp"

class CircleException : public ShapeException {
public:
    CircleException(const std::string& message);
};

#endif // CIRCLEEXCEPTION_HPP
