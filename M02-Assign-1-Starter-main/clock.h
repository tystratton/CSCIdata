#ifndef CLOCK_H
#define CLOCK_H
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <map>
#include "clockexcept.h"

enum hourType
{
    TWELVE = 12,
    TWENTYFOUR = 24
};
enum amPmType
{
    AM,
    PM
};

class clockType
{
public:
    static std::map<hourType, std::string> hourTypeToStr; // = {{TWELVE, "12 hour clock"}, {TWENTYFOUR, "24 hour clock"}};
    static std::map<int, hourType> intToHourType;         // = {{12, TWELVE}, {24, TWENTYFOUR}};
    static std::map<amPmType, std::string> amPmToStr;     // = {{AM, "AM"}, {PM, "PM"}};
    static std::map<std::string, amPmType> strToAmPm;     // = {{"AM", AM}, {"PM", PM}};
    // clockType();
    clockType(int h = 0, int m = 0, int s = 0, hourType = TWENTYFOUR, amPmType = PM); // first parameter is hour, second is minute, third is second.
    void setHour(int h);
    void setMinute(int m);
    void setSecond(int s);
    void setClockType(hourType);
    void setAmPm(amPmType);
    int getHour() const;
    int getMinute() const; // fill in for lecture activity
    int getSecond() const; // fill in for lecture activity
    void incrementSecond();
    void incrementMinute();
    void incrementHour();
    int operator-(const clockType &) const;
    clockType operator+(int) const;
    friend int operator-(clockType &left, int right);
    friend std::ostream &operator<<(std::ostream &, const clockType &);
    clockType operator++();
    clockType operator++(int);
    std::string print() const;
    bool operator>(const clockType &) const;
    bool operator>=(const clockType &) const;
    bool operator==(const clockType &) const;
    bool operator!=(const clockType &) const;
    bool operator<(const clockType &) const;
    bool operator<=(const clockType &) const;

private:
    int hour{};
    int minute{};
    int second{};
    hourType type;
    amPmType timeOfDay;
};

#endif