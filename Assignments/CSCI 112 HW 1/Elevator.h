//
//  Elevator.hpp
//  ElevatorSim
//
//  Created by Sherine Antoun on 4/21/23.
//  Copyright © 2023 Sherine Antoun. All rights reserved.
//  Interface file for the class Elevator  Do NOT alter or submit this header file.

#ifndef Elevator_h
#define Elevator_h
#include <stdio.h>
const int UP = 1, DOWN = -1, STOPPED = 0;
class Elevator
{
    public:
    // constructor for number of floors - no default constructor
        Elevator(int);
    // destructor
        ~Elevator();
    // move one floor in required direction
        void Move();
    // report current status: floor, direction, door status
        void Status(int&,int&,int&);
    // handle rider request outside elevator
        void DirectionSelect(int, int);
    // handle rider request inside elevator
        void ChooseFloor(int);

    private:
        int maxfloor;    // highest numbered floor in the building
        int currentfloor;
        int currentdirection;
        int dooropen;
        int* floorup;    // array for up buttons on floor
        int* floordown;    // array for down buttons
        int* button;    // array of internal buttons
};
#endif /* Elevator_h */
