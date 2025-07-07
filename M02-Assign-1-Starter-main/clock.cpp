#include "clock.h"

std::map<hourType, std::string> clockType::hourTypeToStr = {{TWELVE, "12 hour clock"}, {TWENTYFOUR, "24 hour clock"}};
std::map<amPmType, std::string> clockType::amPmToStr = {{AM, "AM"}, {PM, "PM"}};
std::map<int, hourType> clockType::intToHourType = {{12, TWELVE}, {24, TWENTYFOUR}};
std::map<std::string, amPmType> clockType::strToAmPm = {{"AM", AM}, {"PM", PM}};

void clockType::setHour(int hour)
{
    if (type == TWENTYFOUR)
    {
        if (hour >= 0 && hour <= 23)
        {
            this->hour = hour;
        }
        else
        {
            // hour = 0;
            throw hourException(24);
        }
    }
    else
    {
        if (hour >= 1 && hour <= 12)
        {
            this->hour = hour;
        }
        else
        {
            // hour = 1;
            throw hourException(12);
        }
    }
}

clockType::clockType(int hour, int min, int sec, hourType typ, amPmType tod) : type(typ), timeOfDay(tod)
{

    setHour(hour);
    setMinute(min);
    setSecond(sec);
}

void clockType::setMinute(int min)
{
    if (min >= 0 && min <= 59)
    {
        minute = min;
    }
    else
    {
        throw minuteException();
    }
}

void clockType::setSecond(int sec)
{
    if (sec >= 0 && sec <= 59)
    {
        second = sec;
    }
    else
    {
        throw secondException();
    }
}

void clockType::setClockType(hourType hour)
{
    type = hour;
}

void clockType::setAmPm(amPmType ampm)
{
    timeOfDay = ampm;
}

int clockType::getHour() const
{
    return hour;
}

int clockType::getMinute() const
{
    return minute;
}

int clockType::getSecond() const
{
    return second;
}

void clockType::incrementSecond()
{
    second++;
    if (second > 59)
    {
        second = 0;
        incrementMinute();
    }
}

std::string clockType::print() const
{
    std::ostringstream out;
    out << std::setfill('0');
    out << std::setw(2) << hour << ":";
    out << std::setw(2) << minute << ":";
    out << std::setw(2) << second;
    if (type == TWELVE)
    {
        out << " " << amPmToStr.at(timeOfDay);
    }
    else
    {
        out << std::endl;
        out << hourTypeToStr.at(type) << std::endl;
    }
    return out.str();
}

bool clockType::operator>(const clockType &otherClock) const
{
    int correctH = this->hour; // corrected version for 12 hour clocks
    int ocH = otherClock.hour; // corrected otherclock for 12 hour clocks
    if (this->type == TWELVE && this->timeOfDay == PM && this->hour < 12)
    {
        correctH = this->hour + 12;
    }
    else if (this->type == TWELVE && this->timeOfDay == AM && this->hour == 12)
    {
        correctH = 0;
    }
    if (otherClock.type == TWELVE && otherClock.timeOfDay == PM && otherClock.hour < 12)
    {
        ocH = otherClock.hour + 12;
    }
    else if (otherClock.type == TWELVE && otherClock.timeOfDay == AM && otherClock.hour == 12)
    {
        ocH = 0;
    }

    if (correctH == ocH)
    {
        if (this->minute == otherClock.minute)
        {
            return this->second > otherClock.second;
        }
        return this->minute > otherClock.minute;
    }
    return correctH > ocH;
    return false;
}

bool clockType::operator>=(const clockType &otherClock) const
{
    return *this > otherClock || *this == otherClock;
}

bool clockType::operator==(const clockType &otherClock) const
{
    int cmpHour = this->hour;
    int cmpOthHour = otherClock.hour;
    if (this->type == TWELVE)
    {
        if (this->timeOfDay == PM && this->hour != 12)
        {
            cmpHour = (this->hour + 12) % 24;
        }
    }
    if (otherClock.type == TWELVE)
    {
        if (this->timeOfDay == PM && otherClock.hour != 12)
        {
            cmpOthHour = (otherClock.hour + 12) % 24;
        }
    }
    return cmpHour == cmpOthHour && this->minute == otherClock.minute;
}

bool clockType::operator!=(const clockType &otherClock) const
{
    return !(*this == otherClock);
}

bool clockType::operator<(const clockType &otherClock) const
{

    bool less = false;

    int cmpHour = this->hour;
    int cmpOthHour = otherClock.hour;
    if (this->type == TWELVE)
    {
        if (this->timeOfDay == PM && this->hour != 12)
        {
            cmpHour = (this->hour + 12) % 24;
        }
    }
    if (otherClock.type == TWELVE)
    {
        if (this->timeOfDay == PM && otherClock.hour != 12)
        {
            cmpOthHour = (otherClock.hour + 12) % 24;
        }
    }
    if (cmpHour == cmpOthHour)
    {
        if (this->minute == otherClock.minute)
        {
            if (this->second == otherClock.second)
            {
                less = false;
            }
            else if (this->second < otherClock.second)
            {
                less = true;
            }
            else
            {
                less = false;
            }
        }
        else if (this->minute < otherClock.minute)
        {
            less = true;
        }
        else
        {
            less = false;
        }
    }
    else if (cmpHour < cmpOthHour)
    {
        less = true;
    }
    else
    {
        less = false;
    }
    return less;
}

bool clockType::operator<=(const clockType &otherClock) const
{
    return *this < otherClock || *this == otherClock;
    ;
}

void clockType::incrementMinute()
{
    minute++;
    if (minute > 59)
    {
        minute = 0;
        incrementHour();
    }
}

void clockType::incrementHour()
{
    hour++;
    if (type == TWELVE)
    {
        if (hour == 12)
        {
            timeOfDay == PM ? timeOfDay = AM : timeOfDay = PM; // if timeofday is pm set to am otherwise set to pm.
        }
        if (hour > 12)
        {
            hour = 1;
            // timeOfDay == PM ? timeOfDay = AM : timeOfDay = PM; // if timeofday is pm set to am otherwise set to pm.
        }
    }
    else
    {
        if (hour > 23)
        {
            hour = 0;
        }
    }
}

int clockType::operator-(const clockType &otherClock) const
{
    int diffH = 0;
    int correctH = this->hour; // corrected version for 12 hour clocks
    int ocH = otherClock.hour; // corrected otherclock for 12 hour clocks
    if (this->type == TWELVE && this->timeOfDay == PM && this->hour < 12)
    {
        correctH = this->hour + 12;
    }
    else if (this->type == TWELVE && this->timeOfDay == AM && this->hour == 12)
    {
        correctH = 0;
    }
    if (otherClock.type == TWELVE && otherClock.timeOfDay == PM && otherClock.hour < 12)
    {
        ocH = otherClock.hour + 12;
    }
    else if (otherClock.type == TWELVE && otherClock.timeOfDay == AM && otherClock.hour == 12)
    {
        ocH = 0;
    }

    return abs(correctH - ocH);
}

clockType clockType::operator+(int hours) const
{
    int newHour = this->hour;
    amPmType tod = this->timeOfDay;
    for (int i = 0; i < hours; i++)
    {
        newHour++;
        if (type == TWELVE)
        {
            if (newHour == 12)
            {
                tod == PM ? tod = AM : tod = PM; // if timeofday is pm set to am otherwise set to pm.
            }
            if (newHour > 12)
            {
                newHour = 1;
                // timeOfDay == PM ? timeOfDay = AM : timeOfDay = PM; // if timeofday is pm set to am otherwise set to pm.
            }
        }
        else
        {
            if (newHour > 23)
            {
                newHour = 0;
            }
        }
    }

    return clockType(newHour, this->minute, this->second, this->type, tod);
}

std::ostream &operator<<(std::ostream &out, const clockType &clock)
{
    out << clock.print();
    return out;
}

clockType clockType::operator++()
{
    incrementSecond();
    return *this;
}
clockType clockType::operator++(int)
{
    clockType temp = *this;
    incrementSecond();
    return temp;
}
/*
clockType::clockType()
{
    hour = 0;
    minute = 0;
    second = 0;
}
*/