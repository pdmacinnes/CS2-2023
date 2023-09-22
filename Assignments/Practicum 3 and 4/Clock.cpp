//Implementation file Clock.cpp

#include <iostream>
#include "Clock.h"

using namespace std;

class extClockType : public clockType
{
public:
    extClockType(int hours = 0, int minutes = 0, int seconds = 0, string timeZone = "UTC");

    void setTimeZone(const string& timeZone);
    string getTimeZone() const;

private:
    string timeZone;
};

extClockType::extClockType(int hours, int minutes, int seconds, string timeZone)
    : clockType(hours, minutes, seconds), timeZone(timeZone)
{
}

void extClockType::setTimeZone(const string& timeZone)
{
    this->timeZone = timeZone;
}

string extClockType::getTimeZone() const
{
    return timeZone;
}

class alarmClockType : public extClockType
{
public:
    alarmClockType(int hours = 0, int minutes = 0, int seconds = 0, string timeZone = "UTC", bool isAM = true);

    void setAM(bool isAM);
    bool isAM() const;

private:
    bool isMorning;
};

alarmClockType::alarmClockType(int hours, int minutes, int seconds, string timeZone, bool isAM)
    : extClockType(hours, minutes, seconds, timeZone), isMorning(isAM)
{
}

void alarmClockType::setAM(bool isAM)
{
    isMorning = isAM;
}

bool alarmClockType::isAM() const
{
    return isMorning;
}


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
