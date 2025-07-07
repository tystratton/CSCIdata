/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 6/16/2025
Purpose: Time Program Module 2 Assignment 2, learning linked lists*/

#include <iostream>
#include <string>
#include <limits>
#include <regex>
#include "priority_queue.h"
#include "bug_report.h"
#include "linkedList.h"

void displayMenu();
bool isValidDate(const std::string &date);
void getBugReport(PriorityQueue<BugReport> &bugQueue);

int main()
{
    PriorityQueue<BugReport> bugQueue;
    linkedList<BugReport> completedBugs;
    int choice = 0;

    while (choice != 3)
    {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            choice = 0;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline

        switch (choice)
        {
        case 1:
            getBugReport(bugQueue);
            break;
        case 2:
            if (bugQueue.isEmpty())
            {
                std::cout << "\nNo pending bug reports to distribute." << std::endl;
            }
            else
            {
                BugReport distributedBug = bugQueue.dequeue();
                std::cout << "\n--- Distributed Bug Report ---" << std::endl;
                std::cout << distributedBug << std::endl;
                completedBugs.insertLast(distributedBug);
            }
            break;
        case 3:
            std::cout << "\n--- Completed Bug Reports ---" << std::endl;
            if (completedBugs.isEmptyList())
            {
                std::cout << "No completed bug reports." << std::endl;
            }
            else
            {
                completedBugs.printList();
            }

            std::cout << "\n--- Uncompleted Bug Reports ---" << std::endl;
            if (bugQueue.isEmpty())
            {
                std::cout << "No uncompleted bug reports." << std::endl;
            }
            else
            {
                bugQueue.print();
            }
            std::cout << "\nExiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }

    return 0;
}

void displayMenu()
{
    std::cout << "\n--- Bug Tracker Menu ---" << std::endl;
    std::cout << "1. Enter Bug Report" << std::endl;
    std::cout << "2. Distribute Bug Report" << std::endl;
    std::cout << "3. Quit" << std::endl;
}

bool isValidDate(const std::string &date)
{
    const std::regex pattern(R"(\d{4}-\d{2}-\d{2})");
    return std::regex_match(date, pattern);
}

void getBugReport(PriorityQueue<BugReport> &bugQueue)
{
    std::string date, reporter, description;
    int priority;

    std::cout << "Enter the date of the report (yyyy-mm-dd): ";
    std::getline(std::cin, date);
    while (!isValidDate(date))
    {
        std::cout << "The date entered is not valid. Please check that the date entered is in the correct format." << std::endl;
        std::cout << "Enter the date of the report (yyyy-mm-dd): ";
        std::getline(std::cin, date);
    }

    std::cout << "Enter the name of the reporter: ";
    std::getline(std::cin, reporter);

    std::cout << "Describe the bug: ";
    std::getline(std::cin, description);

    std::cout << "What is the priority 1 - 10 (1 is low, 10 is high): ";
    std::cin >> priority;
    while (std::cin.fail() || priority < 1 || priority > 10)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number between 1 and 10." << std::endl;
        std::cout << "What is the priority 1 - 10 (1 is low, 10 is high): ";
        std::cin >> priority;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline

    bugQueue.enqueue(BugReport(date, reporter, description, priority));
    std::cout << "Bug report successfully added." << std::endl;
}
