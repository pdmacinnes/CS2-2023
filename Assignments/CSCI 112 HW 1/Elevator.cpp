//
//  Elevator.cpp
//  ElevatorSim
//
//  Created by Sherine Antoun on 4/21/20.
//  Copyright © 2020 Sherine Antoun. All rights reserved.
//

#include "Elevator.h"
// constructor for number of floors - no default constructor
Elevator::Elevator(int floors)
{
    
}
// destructor
Elevator::~Elevator()
{
   
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
   
    //direction is up but all requests are from below
   //some if test here
    //keep going downwards
    else if(currentdirection==1&&!requestAbove&&requestBelow)
    {
        currentdirection==-1;
        currentfloor--;
    }
    //direction is down but all requests are from above
   
    //deal with no request so go into idell mode
    else if(!requestAbove&&1requestBelow)
    {
        currentdirection=0;
    }
    //stoped now move on request above
    
    //stoped now move on request below
    
    //reset requests
    requestBelow==false;
    requestAbove==false;
    //now that a move was completed - again determine where requests originate from:
    
       //look for direction of button pusheds from above

       //look for direction of button pusheds from below
       
    //check the current floor for any request
    
    //now again since we have moved determine if the new direction - no move just determine ...
    //direction up no change
  
    //direction is up but requests are from below
    
    //keep direction down
    
    //direction down all requests are from above
    
    //regardless of direction we have no requests - idel
    
    //stopped and move according to request
    else if(currentdirection-0&&requestAbove)
    {
        currentdirection = 1;
    }
    
    //check buttons to do with current floor to open and close doors as needed .. safely then reset em
    
    //floorup reset
    if (currentdirection==1 && floorup(currentfloor))
    {
        if(!dooropen)
            dooropen=true;
        floorup[currentfloor]=false;
    }
    if (currentdirection==-1 && floordown(currentfloor))
    {
        if(!dooropen)
            dooropen=true;
        floordown[currentfloor]=false;
    }
    if (button(currentfloor))
    {
            dooropen=true;
        button[currentfloor]=false;
    }
}
//talk to the driver program
void Elevator::Status(int& currentFloor, int& currDir,int& doorIsOpen)
{
   
}

// handle rider request outside elevator
void Elevator::DirectionSelect(int floorNum, int direction)
{
   
// handle rider request inside elevator



}
