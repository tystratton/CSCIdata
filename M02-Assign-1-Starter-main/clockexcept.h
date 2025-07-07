#ifndef CLOCKEXCEPT_H
#define CLOCKEXCEPT_H
#include <string>

class hourException
{
public:
    hourException(int);
    std::string what();

private:
    std::string msg;
};
class minuteException
{
public:
    minuteException();
    std::string what();

private:
    std::string msg;
};
class secondException
{
public:
    secondException();
    std::string what();

private:
    std::string msg;
};
#endif