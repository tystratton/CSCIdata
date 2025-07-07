/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 6/16/2025
Purpose: Time Program Module 2 Assignment 1, learning regex*/
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>
#include "clock.h"

using namespace std;

int main()
{
    vector<clockType> timeVector;
    string input;
    
    // REGEX
    // Pattern for h:mm:ss AM/PM or hh:mm:ss AM/PM
    regex pattern1(R"(^(\d{1,2}):(\d{2}):(\d{2})\s+(AM|PM|am|pm)$)");
    
    // Pattern for h:mm AM/PM or hh:mm AM/PM  
    regex pattern2(R"(^(\d{1,2}):(\d{2})\s+(AM|PM|am|pm)$)");
    
    // Pattern for h:mm:ss or hh:mm:ss (24-hour)
    regex pattern3(R"(^(\d{1,2}):(\d{2}):(\d{2})$)");
    
    // Pattern for h:mm or hh:mm (24-hour)
    regex pattern4(R"(^(\d{1,2}):(\d{2})$)");
    
    smatch matches;
    
    cout << "Enter times in various formats (type 'quit' to exit):" << endl;
    cout << "Supported formats:" << endl;
    cout << "  12-hour: h:mm:ss AM/PM, hh:mm:ss AM/PM, h:mm AM/PM, hh:mm AM/PM" << endl;
    cout << "  24-hour: h:mm:ss, hh:mm:ss, h:mm, hh:mm" << endl;
    cout << endl;
    
    while (true) {
        cout << "Enter a time: ";
        getline(cin, input);
        
        // Check if user wants to quit
        if (input == "quit") {
            break;
        }
        
        try {
            bool validTime = false;
            clockType clock;
            
            // Check pattern 1: h:mm:ss AM/PM or hh:mm:ss AM/PM
            if (regex_match(input, matches, pattern1)) {
                int hour = stoi(matches[1].str());
                int minute = stoi(matches[2].str());
                int second = stoi(matches[3].str());
                string ampm = matches[4].str();
                
                // Convert ampm to uppercase for comparison
                transform(ampm.begin(), ampm.end(), ampm.begin(), ::toupper);
                amPmType timeOfDay = (ampm == "AM") ? AM : PM;
                
                clock = clockType(hour, minute, second, TWELVE, timeOfDay);
                validTime = true;
            }
            // Check pattern 2: h:mm AM/PM or hh:mm AM/PM
            else if (regex_match(input, matches, pattern2)) {
                int hour = stoi(matches[1].str());
                int minute = stoi(matches[2].str());
                int second = 0; // default seconds to 0
                string ampm = matches[3].str();
                
                // Convert ampm to uppercase for comparison
                transform(ampm.begin(), ampm.end(), ampm.begin(), ::toupper);
                amPmType timeOfDay = (ampm == "AM") ? AM : PM;
                
                clock = clockType(hour, minute, second, TWELVE, timeOfDay);
                validTime = true;
            }
            // Check pattern 3: h:mm:ss or hh:mm:ss (24-hour)
            else if (regex_match(input, matches, pattern3)) {
                int hour = stoi(matches[1].str());
                int minute = stoi(matches[2].str());
                int second = stoi(matches[3].str());
                
                clock = clockType(hour, minute, second, TWENTYFOUR, PM);
                validTime = true;
            }
            // Check pattern 4: h:mm or hh:mm (24-hour)
            else if (regex_match(input, matches, pattern4)) {
                int hour = stoi(matches[1].str());
                int minute = stoi(matches[2].str());
                int second = 0; // default seconds to 0
                
                clock = clockType(hour, minute, second, TWENTYFOUR, PM);
                validTime = true;
            }
            
            if (validTime) {
                timeVector.push_back(clock);
                cout << "Time added successfully: " << clock.print();
            } else {
                cout << "Invalid time format. Please try again." << endl;
            }
            
        } catch (hourException& e) {
            cout << "Error: " << e.what() << endl;
        } catch (minuteException& e) {
            cout << "Error: " << e.what() << endl;
        } catch (secondException& e) {
            cout << "Error: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "Error: Invalid time format. Please try again." << endl;
        }
    }
    
    // Display all valid times
    cout << "\nAll valid times entered:" << endl;
    if (timeVector.empty()) {
        cout << "No valid times were entered." << endl;
    } else {
        for (size_t i = 0; i < timeVector.size(); i++) {
            cout << timeVector[i].print();
        }
    }
    
    return 0;
}