#include "BugReport.h"

// Constructor
BugReport::BugReport(int id, const std::string &description, const std::string &reporter, const std::string &status, int priority, const std::string &date)
    : id(id), description(description), reporter(reporter), status(status), priority(priority), date(date) {}

// Getters
int BugReport::getId() const
{
    return id;
}

std::string BugReport::getDescription() const
{
    return description;
}

std::string BugReport::getReporter() const
{
    return reporter;
}

std::string BugReport::getStatus() const
{
    return status;
}

int BugReport::getPriority() const
{
    return priority;
}

std::string BugReport::getDate() const
{
    return date;
}

// Setters
void BugReport::setDescription(const std::string &description)
{
    this->description = description;
}

void BugReport::setReporter(const std::string &reporter)
{
    this->reporter = reporter;
}

void BugReport::setStatus(const std::string &status)
{
    this->status = status;
}

void BugReport::setPriority(int priority)
{
    this->priority = priority;
}

void BugReport::setDate(const std::string &date)
{
    this->date = date;
}

// Comparison operators
bool BugReport::operator==(const BugReport &other) const
{
    return this->priority == other.priority;
}

bool BugReport::operator!=(const BugReport &other) const
{
    return !(*this == other);
}

bool BugReport::operator<(const BugReport &other) const
{
    return this->priority < other.priority;
}

bool BugReport::operator<=(const BugReport &other) const
{
    return this->priority <= other.priority;
}

bool BugReport::operator>(const BugReport &other) const
{
    return this->priority > other.priority;
}

bool BugReport::operator>=(const BugReport &other) const
{
    return this->priority >= other.priority;
}

// Friend function to overload the output stream operator
std::ostream &operator<<(std::ostream &os, const BugReport &report)
{
    os << "BugReport ID: " << report.id << "\n"
       << "Description: " << report.description << "\n"
       << "Reporter: " << report.reporter << "\n"
       << "Status: " << report.status << "\n"
       << "Priority: " << report.priority << "\n"
       << "Date: " << report.date << "\n";
    return os;
}
