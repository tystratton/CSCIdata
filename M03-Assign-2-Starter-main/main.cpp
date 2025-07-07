/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 6/23/2025
Purpose: Time Program Module 3 Assignment 2, learning priority queues*/

#include <iostream>
#include <string>
#include <regex>
#include <limits>
#include "priorityQueue.h"

void displayMenu();
void addBugReport(priorityQueue<BugReport>& bugQueue, int& idCounter);
void distributeBugReport(priorityQueue<BugReport>& bugQueue, unorderedLinkedList<BugReport>& completedList);
void quitProgram(priorityQueue<BugReport>& bugQueue, unorderedLinkedList<BugReport>& completedList);

int main() {
    priorityQueue<BugReport> bugQueue;
    unorderedLinkedList<BugReport> completedReports;
    int choice;
    int idCounter = 1;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        switch (choice) {
            case 1:
                addBugReport(bugQueue, idCounter);
                break;
            case 2:
                distributeBugReport(bugQueue, completedReports);
                break;
            case 3:
                quitProgram(bugQueue, completedReports);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

void displayMenu() {
    std::cout << "\nPlease choose from the following menu: \n"
              << "1. Enter Bug Report\n"
              << "2. Distribute Bug Report\n"
              << "3. Quit\n\n";
}

void addBugReport(priorityQueue<BugReport>& bugQueue, int& idCounter) {
    std::string date, reporter, description;
    int priority;
    const std::regex datePattern(R"(^(\d{4})-(0?[1-9]|1[0-2])-(0?[1-9]|[1-2][0-9]|3[0-1])$)");

    std::cout << "Enter the date of the report (yyyy-mm-dd): ";
    std::getline(std::cin, date);
    
    while (!std::regex_match(date, datePattern)) {
        // Clear any error flags on the input stream
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        std::cout << "The date entered is not valid. Please check that the date entered is in the correct format.\n";
        std::cout << "Enter the date of the report (yyyy-mm-dd): ";
        std::getline(std::cin, date);
    }

    std::cout << "Enter the name of the reporter: ";
    std::getline(std::cin, reporter);
    std::cout << "Describe the bug: ";
    std::getline(std::cin, description);
    std::cout << "What is the priority 1 - 10 (1 is low, 10 is high): ";
    std::cin >> priority;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    BugReport newReport(idCounter++, description, reporter, "Open", priority, date);
    bugQueue.insert(newReport);
}

void distributeBugReport(priorityQueue<BugReport>& bugQueue, unorderedLinkedList<BugReport>& completedList) {
    if (bugQueue.isEmptyList()) {
        std::cout << "No bug reports to distribute.\n";
    } else {
        BugReport report = bugQueue.front();
        report.setStatus("In Progress");
        std::cout << "\nBug Report:\n" << report << std::endl;
        completedList.insert(report);
        bugQueue.dequeue();
    }
}

void quitProgram(priorityQueue<BugReport>& bugQueue, unorderedLinkedList<BugReport>& completedList) {
    std::cout << "\n--- Completed Bug Reports ---\n";
    if (completedList.isEmptyList()) {
        std::cout << "No completed bug reports.\n";
    } else {
        std::cout << completedList.print();
    }

    std::cout << "\n--- Uncompleted Bug Reports ---\n";
    if (bugQueue.isEmptyList()) {
        std::cout << "No uncompleted bug reports.\n";
    } else {
        std::cout << bugQueue.print();
    }
    
    // Empty the queue
    bugQueue.destroyList();
    std::cout << "\nAll bug reports processed. Exiting.\n";
}
