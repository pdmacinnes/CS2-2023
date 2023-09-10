//
//  Elevator.cpp
//  ElevatorSim
//
//  Created by Sherine Antoun on 4/21/20.
//  Copyright © 2020 Sherine Antoun. All rights reserved.
//

#include <iostream>
#include "Elevator.h"
// constructor for number of floors - no default constructor
Elevator::Elevator(int floors) : maxfloor(floors), currentfloor(0), currentdirection(0), dooropen(0)
{
    floorup = new int[maxfloor];
    floordown = new int[maxfloor];
    button = new int[maxfloor];

    for (int i = 0; i < maxfloor; i++) 
    {
        floorup[i] = 0;
        floordown[i] = 0;
        button[i] = 0;
    }
}
// destructor
Elevator::~Elevator()
{
    delete[] floorup;
    delete[] floordown;
    delete[] button;
}

// move one floor in required direction
void Elevator::Move()
{
    //determine if we have requests above or below
    bool requestAbove = false;
    bool requestBelow = false;
    
    //before moving check doors are closed
    if(dooropen)dooropen = false;
    
    //workout which floor is requesting elevator (above or below)
    for (int i = currentfloor; i<=maxfloor;i++)
    {
        if(((floorup[i]||floordown[i]||button[i]) && (maxfloor!=currentfloor)&&(i!=currentfloor)))
            requestAbove=true;
    }
    for (int i = currentfloor; i>=0; i--)
    {
        if(((floorup[i]||floordown[i]||button[i]) && (0!=currentfloor)&&(0!=currentfloor)))
            requestBelow=true;
    }
       
    //keep direction up
    if (currentdirection == 0 && requestAbove) 
    {
        currentdirection = 1;
    }

   //direction is up but all requests are from below
    if (currentdirection == 1 && !requestAbove && requestBelow)
    {
        currentdirection = -1;
        currentfloor--;
    }

   //some if test here
    //keep going downwards
    else if(currentdirection==1&&!requestAbove&&requestBelow)
    {
        currentdirection =-1;
        currentfloor--;
    }

    //direction is down but all requests are from above
    if (currentdirection == -1 && !requestBelow && requestAbove)
    {
        currentdirection = 1;
        currentfloor++;
    }

    //deal with no request so go into idell mode
    else if(!requestAbove&&!requestBelow)
    {
        currentdirection=0;
    }

    //stoped now move on request above
    if (currentdirection == 0 && requestAbove)
    {
        currentdirection = 1;
    }

    //stoped now move on request below
    if (currentdirection == 0 && requestBelow)
    {
        currentdirection = -1;
    }

    //reset requests
    requestBelow=false;
    requestAbove=false;
    //now that a move was completed - again determine where requests originate from:
    
       //look for direction of button pusheds from above
    for (int i = currentfloor + 1; i <= maxfloor; i++)
    {
        if (button[i])
        {
            currentdirection = 1;
        }
    }

    //look for direction of button pusheds from below
    for (int i = currentfloor - 1; i >= maxfloor; i--)
    {
        if (button[i])
        {
            currentdirection = -1;
        }
    }

    //check the current floor for any request
    if (button[currentfloor])
    {
        dooropen = true;
        button[currentfloor] = false;
    }

    //now again since we have moved determine if the new direction - no move just determine ...
    //direction up no change
  
    //direction is up but requests are from below
    if (currentdirection == 1 && requestBelow)
    {
        currentdirection = -1;
    }

    //keep direction down
    
    //direction down all requests are from above
    if (currentdirection == -1 && requestAbove)
    {
        currentdirection = 1;
    }

    //regardless of direction we have no requests - idel
    if (currentdirection != 0 && !requestAbove && !requestBelow)
    {
        currentdirection = 0;
    }

    //stopped and move according to request
    else if(currentdirection == 0 && requestAbove)
    {
        currentdirection = 1;
    }
    
    //check buttons to do with current floor to open and close doors as needed .. safely then reset em
    
    //floorup reset
    if (currentdirection==1 && floorup[currentfloor])
    {
        if(!dooropen)
            dooropen=true;
        floorup[currentfloor]=false;
    }
    if (currentdirection==-1 && floordown[currentfloor])
    {
        if(!dooropen)
            dooropen=true;
        floordown[currentfloor]=false;
    }
    if (button[currentfloor])
    {
        dooropen=true;
        button[currentfloor]=false;
    }
}

//talk to the driver program
void Elevator::Status(int& currentFloor, int& currDir,int& doorIsOpen)
{
    currentFloor = currentfloor;
    currDir = currentdirection;
    doorIsOpen = dooropen;
}

// handle rider request outside elevator
void Elevator::DirectionSelect(int floorNum, int direction)
{
   if (floorNum >= 0 && floorNum < maxfloor)
   {
    if (direction == 1)
    {
        floorup[floorNum] = 1;
    }
    else if (direction == -1)
    {
        floordown[floorNum] = 1;
    }
   }

   // handle rider request inside elevator
   else
   {
    std::cerr << "Invalid request: Floor number does not exist." << std::endl;
   }
}