//
//
//  ElevatorSim Assignment
//
//  Created by Sherine Antoun on 4/21/23.
//  Copyright © 2023 Sherine Antoun. All rights reserved.
//
//  ClassPrac.cpp
//  Driver program to test the class Elevator
//  Written by Sherine Antoun
//  Note that this is NOT the way the simulation would normally
//  be carried out.  It is a quick fix just for test purposes.
//  Do Not Alter or Submit this file

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Elevator.h"

const int NOT_YET = -1;
const int WAIT = 0;
const int ON = 1;
const int OFF = 2;

struct RiderType
{
    int arrivetime;
    int floorstart;
    int floorfinish;
    int status;
};

int getRandomNumber(int a, int b)
{
    if (a > b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    return (rand() % (b - a + 1) + a);
}

int main(int argc, const char * argv[])
{
    const int NRIDERS = 12;
    const int MAXFLOOR = 10;

    RiderType rider[NRIDERS];
    Elevator e(MAXFLOOR);
    int i, t, floor, direction, door, lastrider = 0;
    bool finished = false;
    int seed;

    seed = 54321;
    srand(seed);

    t = 0;
    std::cout << "Start of simulation of elevator. " << MAXFLOOR + 1 << " floors.\n\n";

    for (i = 0; i < NRIDERS; i++)
    {
        t = t + getRandomNumber(0, 5);
        rider[i].arrivetime = t;
        rider[i].floorstart = getRandomNumber(0, MAXFLOOR);
        do
            rider[i].floorfinish = getRandomNumber(0, MAXFLOOR);
        while (rider[i].floorfinish == rider[i].floorstart);
        rider[i].status = NOT_YET;
    }

    t = 0;
    while (!finished)
    {
        e.Move();
        e.Status(floor, direction, door);

        std::cout << "T" << t << ".\tElevator is on floor " << floor << " with the doors ";
        if (door)
            std::cout << "open.";
        else
            std::cout << "closed.";

        if (direction == UP)
            std::cout << " Going up.";
        else if (direction == DOWN)
            std::cout << " Going down.";
        else
            std::cout << " Stopped.";

        std::cout << std::endl;

        i = lastrider;
        while (i < NRIDERS && rider[i].arrivetime <= t)
        {
            if (rider[i].status == NOT_YET)
            {
                rider[i].status = WAIT;
                std::cout << "\tRider " << i + 1 << " arrives at floor " << rider[i].floorstart
                          << " and presses the button to go ";
                lastrider = i;
                if (rider[i].floorfinish > rider[i].floorstart)
                {
                    std::cout << "up." << std::endl;
                    e.DirectionSelect(rider[i].floorstart, UP);
                } else
                {
                    std::cout << "down." << std::endl;
                    e.DirectionSelect(rider[i].floorstart, DOWN);
                }
            }
            i++;
        }

        finished = true;
        for (i = 0; i <= lastrider; i++)
        {
            if ((rider[i].status == WAIT) && (rider[i].floorstart == floor) && door)
            {
                if ((rider[i].floorfinish - rider[i].floorstart) * direction >= 0 || getRandomNumber(0, 1) == 0)
                {
                    std::cout << "\tRider " << i + 1 << " enters elevator and presses floor "
                              << rider[i].floorfinish << " button." << std::endl;
                    e.ChooseFloor(rider[i].floorfinish);
                    rider[i].status = ON;
                }
                else
                {
                    std::cout << "\tRider " << i + 1 << " continues to wait." << std::endl;
                }
            }
            else if ((rider[i].status == ON) && (rider[i].floorfinish == floor))
            {
                std::cout << "\tRider " << i + 1 << " leaves elevator." << std::endl;
                rider[i].status = OFF;
            }
            if (rider[i].status != OFF)
                finished = false;
        }
        t++; // tick the clock forward
    }

    std::cout << "END OF SIMULATION" << std::endl;
    return 0;
}
