#ifndef BUG_REPORT_H
#define BUG_REPORT_H

#include <iostream>
#include <string>

class BugReport
{
public:
    BugReport(const std::string &date = "", const std::string &reporter = "",
              const std::string &description = "", int priority = 1);

    // Overloaded operators for comparison based on priority
    bool operator<(const BugReport &other) const;
    bool operator>(const BugReport &other) const;
    bool operator==(const BugReport &other) const;

    // Friend function to overload the stream insertion operator for easy printing
    friend std::ostream &operator<<(std::ostream &os, const BugReport &report);

private:
    std::string reportDate;
    std::string reporterName;
    std::string bugDescription;
    int priorityLevel;
};

#endif // BUG_REPORT_H 