CSCI 112 Data Structures
Practicum   Demo Due in class on Friday next week



Derive the class extClockType from the class clockType (below) by adding a member variable to store the time zone.

Add the necessary member functions and constructors to make the class functional.

Also, write the definitions of the member functions and the constructors.

Derive the class alarmClockType the class ClockType by adding the necessary member functions and constructors to make the class functional.

The alarm should identify the trigger time AM from PM.
    
Finally, write a test program to test your derived classes.



    //Header file Clock.h

    #ifndef H_Clock
    #define H_Clock

    #include <iostream>

    using namespace std;

    class clockType
    {
        friend ostream& operator << (ostream&, const clockType&);
        friend istream& operator >> (istream&, clockType&);

    public:
       void setTime(int hours, int minutes, int seconds);
          //Function to set the private data members
          //hr, min, and sec.
          //Postcondition: hr = hours; min = minutes; sec = seconds

       void getTime(int& hours, int& minutes, int& seconds) const;
          //Function to return the time.
          //Postcondition: hours = hr; minutes = min; seconds = sec

       clockType operator++();
          //Overload the pre-increment operator.
          //Postcondition: The time is incremented by one second.
       bool operator==(const clockType& otherClock) const;
          //Overload the equality operator.
          //Postcondition: Returns true if this time is equal to
          //       otherTime, otherwise it returns the value false.

       bool operator<=(const clockType& otherClock) const;
          //Overload the less than or equal to operator.
          //Postcondition: Returns true if the time is less than
          //     or equal to otherTime, otherwise it returns the
          //     value false.

       clockType(int hours = 0, int minutes = 0, int seconds = 0);
          //Constructor to initialize the object with the values
          //specified by the user. If no values are specified,
          //the default values are assumed.
          //Postcondition: Returns: hr = hours; min = minutes;
          //                        sec = seconds

    private:
        int hr;  //variable to store the hours
        int min;  //variable to store the minutes
        int sec;  //variable to store the seconds
    };



    #endif

    //Implementation file Clock.cpp

    #include <iostream>
    #include "Clock.h"

    using namespace std;

    //overload the pre-increment operator
    clockType clockType::operator++()
    {
        sec++;                  //Step a

        if (sec > 59)              //Step b
        {
            sec = 0;            //Step b.1

            min++;                //Step b.2

            if (min > 59)        //Step b.3
            {
                min = 0;        //Step b.3.1

                hr++;            //Step b.3.2

                if (hr > 23)        //Step b.3.3
                    hr = 0;        //Step b.3.3.1
            }
        }
       
        return *this;           //Step c
    }

    //overload the equality operator
    bool clockType::operator==(const clockType& otherClock) const
    {
        return(hr == otherClock.hr && min == otherClock.min
               && sec == otherClock.sec);
    }

    //overload the less than or equal to operator
    bool clockType::operator<=(const clockType& otherClock) const
    {
       return((hr < otherClock.hr) ||
            (hr == otherClock.hr && min < otherClock.min) ||
            (hr == otherClock.hr && min == otherClock.min &&
                     sec <= otherClock.sec));
    }

    //constructor with parameters
    clockType::clockType(int hours, int minutes, int seconds)
    {
        if (0 <= hours && hours < 24)
            hr = hours;
        else
            hr = 0;

        if (0 <= minutes && minutes < 60)
            min = minutes;
        else
            min = 0;

        if (0 <= seconds && seconds < 60)
            sec = seconds;
        else
            sec = 0;
    }

    void clockType::setTime(int hours, int minutes, int seconds)
    {
        if (0 <= hours && hours < 24)
            hr = hours;
        else
            hr = 0;

        if (0 <= minutes && minutes < 60)
            min = minutes;
        else
            min = 0;

        if (0 <= seconds && seconds < 60)
            sec = seconds;
        else
            sec = 0;
    }

    void clockType::getTime(int& hours, int& minutes, int& seconds) const
    {
        hours = hr;
        minutes = min;
        seconds = sec;
    }

    //overload the stream insertion operator
    ostream& operator <<  (ostream& osObject, const clockType& timeOut)
    {
        if (timeOut.hr < 10)
            osObject << '0';
        osObject << timeOut.hr << ':';
        
         if (timeOut.min < 10)
            osObject << '0';
        osObject << timeOut.min << ':';
        
        if (timeOut.sec < 10)
            osObject << '0';
        osObject << timeOut.sec;

        return osObject;    //return the ostream object
    }

       //overload the stream extraction operator
    istream& operator >>  (istream& isObject, clockType& timeIn)
    {
        char ch;

        isObject >> timeIn.hr;      //Step a
        isObject.get(ch);         //Step b; read and discard :
        isObject >> timeIn.min;   //Step c
        isObject.get(ch);         //Step d; read and discard :
        isObject >> timeIn.sec;   //Step e

        return isObject;          //Step f
    }


    //Client program that uses the class clockType

    #include <iostream>
    #include "Clock.h"

    using namespace std;

    int main(int argc, const char* argv[])
    {
        clockType myClock(5, 6, 23);                    //Line 1
        clockType yourClock;                            //Line 2

        cout << "Line 3: myClock = " << myClock
             << endl;                                    //Line 3
        cout << "Line 4: yourClock = " << yourClock
             << endl;                                    //Line 4

        cout << "Line 5: Enter the time in the form "
             << "hr:min:sec ";                            //Line 5
        cin >> myClock;                                    //Line 6
        cout << "Line 7: The new time of myClock = "
             << myClock << endl;                        //Line 7

        ++myClock;                                        //Line 8

        cout << "Line 9: After incrementing the time, "
             << "myClock = " << myClock << endl;        //Line 9

        yourClock.setTime(13, 35, 38);                    //Line 10
        cout << "Line 11: After setting the time, "
             << "yourClock = " << yourClock << endl;    //Line 11

        if (myClock == yourClock)                        //Line 12
            cout << "Line 13: The times of myClock and "
                 << "yourClock are equal" << endl;        //Line 13
        else                                            //Line 14
            cout << "Line 15: The times of myClock and "
                 << "yourClock are not equal" << endl;    //Line 15

        if (myClock <= yourClock)                        //Line 16
            cout << "Line 17: The time of myClock is "
                 << "less than or equal to " << endl
                 << "the time of yourClock" << endl;    //Line 17
        else                                            //Line 18
            cout << "Line 19: The time of myClock is "
                 << "greater than the time of yourClock"
                 << endl;                                //Line 19

        return 0;
    }
