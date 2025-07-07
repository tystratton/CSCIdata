#include "bug_report.h"

BugReport::BugReport(const std::string &date, const std::string &reporter,
                     const std::string &description, int priority)
    : reportDate(date), reporterName(reporter), bugDescription(description), priorityLevel(priority) {}

// Overload < operator for descending priority sort
bool BugReport::operator<(const BugReport &other) const
{
    return this->priorityLevel > other.priorityLevel;
}

// Overload > operator for descending priority sort
bool BugReport::operator>(const BugReport &other) const
{
    return this->priorityLevel < other.priorityLevel;
}

bool BugReport::operator==(const BugReport &other) const
{
    return this.priorityLevel == other.priorityLevel && this.reportDate == other.reportDate && this.reporterName == other.reporterName;
}

std::ostream &operator<<(std::ostream &os, const BugReport &report)
{
    os << "-------------------------" << std::endl;
    os << "Date: " << report.reportDate << std::endl;
    os << "Reporter: " << report.reporterName << std::endl;
    os << "Priority: " << report.priorityLevel << std::endl;
    os << "Description: " << report.bugDescription << std::endl;
    os << "-------------------------";
    return os;
} 