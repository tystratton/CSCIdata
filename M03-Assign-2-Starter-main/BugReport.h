#ifndef BUGREPORT_H
#define BUGREPORT_H

#include <string>
#include <iostream>

class BugReport
{
public:
    // Constructor
    BugReport(int id, const std::string &description, const std::string &reporter, const std::string &status, int priority, const std::string &date);

    // Getters
    int getId() const;
    std::string getDescription() const;
    std::string getReporter() const;
    std::string getStatus() const;
    int getPriority() const;
    std::string getDate() const;

    // Setters
    void setDescription(const std::string &description);
    void setReporter(const std::string &reporter);
    void setStatus(const std::string &status);
    void setPriority(int priority);
    void setDate(const std::string &date);

    // Comparison operators
    bool operator==(const BugReport &other) const;
    bool operator!=(const BugReport &other) const;
    bool operator<(const BugReport &other) const;
    bool operator<=(const BugReport &other) const;
    bool operator>(const BugReport &other) const;
    bool operator>=(const BugReport &other) const;

    // Friend function to overload the output stream operator
    friend std::ostream &operator<<(std::ostream &os, const BugReport &report);

private:
    int id;
    std::string description;
    std::string reporter;
    std::string status;
    int priority;
    std::string date;
};

#endif // BUGREPORT_H
