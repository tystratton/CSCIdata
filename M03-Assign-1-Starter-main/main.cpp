/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 6/23/2025
Purpose: Time Program Module 3 Assignment 1, learning stacks*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>
#include <utility>
#include "url.h"
#include "stack.h"

void resetStream();
void codeGradeLoopFix(std::string errLocation);
void displayMenu(stackType<Url> &backStack, stackType<Url> &forwardStack);

int main()
{
    stackType<Url> backStack(50);
    stackType<Url> forwardStack(50);
    Url *currentUrl = nullptr;
    std::vector<std::pair<std::string, std::string>> urlList;
    int nextUrlIndex = 0;

    std::ifstream navFile("navigation.txt");
    if (!navFile)
    {
        std::cerr << "Error: Could not open navigation.txt" << std::endl;
        return 1;
    }

    std::string url, filename;
    while (navFile >> url >> filename)
    {
        urlList.push_back({url, filename});
    }
    navFile.close();

    if (urlList.empty())
    {
        std::cerr << "Error: navigation.txt is empty or could not be read." << std::endl;
        return 1;
    }

    int choice = 0;
    do
    {
        displayMenu(backStack, forwardStack);

        std::cin >> choice;

        if (std::cin.fail())
        {
            resetStream();
            choice = 0; // Reset choice to prevent exiting loop
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            if (currentUrl != nullptr)
            {
                backStack.push(*currentUrl);
                delete currentUrl;
                currentUrl = nullptr;
            }
            if (!forwardStack.isEmptyStack())
            {
                forwardStack.initializeStack();
            }

            std::string nextUrlStr = urlList[nextUrlIndex].first;
            std::string nextFilename = urlList[nextUrlIndex].second;
            currentUrl = new Url(nextUrlStr, nextFilename);
            currentUrl->displayFileContents();

            nextUrlIndex = (nextUrlIndex + 1) % urlList.size();
            break;
        }
        case 2:
        {
            if (backStack.isEmptyStack())
            {
                std::cout << "That is an invalid choice." << std::endl;
                break;
            }
            else
            {
                if (currentUrl != nullptr)
                {
                    forwardStack.push(*currentUrl);
                    delete currentUrl;
                    currentUrl = nullptr;
                }
                Url temp = backStack.top();
                backStack.pop();
                currentUrl = new Url(temp);
                currentUrl->displayFileContents();
                break;
            }
        }
        case 3:
        {
            if (forwardStack.isEmptyStack())
            {
                std::cout << "That is an invalid choice." << std::endl;
                break;
            }
            else
            {
                if (currentUrl != nullptr)
                {
                    backStack.push(*currentUrl);
                    delete currentUrl;
                    currentUrl = nullptr;
                }
                Url temp = forwardStack.top();
                forwardStack.pop();
                currentUrl = new Url(temp);
                currentUrl->displayFileContents();
                break;
            }
        }
        case 4:
            // std::cout << "Exiting browser. Goodbye!" << std::endl;
            break;
        default:
            std::cout << "That is an invalid choice." << std::endl;
            break;
        }
    } while (choice != 4);

    if (currentUrl != nullptr)
    {
        delete currentUrl;
    }

    return 0;
}

void displayMenu(stackType<Url> &backStack, stackType<Url> &forwardStack)
{
    static bool firstCall = true;
    if (firstCall) {
        firstCall = false;
    } else {
        std::cout << std::endl;
    }
    std::cout << "What would you like to do? " << std::endl;
    std::cout << "1. Navigate to a new URL" << std::endl;
    if (!backStack.isEmptyStack())
    {
        std::cout << "2. Go Back to the previous URL" << std::endl;
    }
    if (!forwardStack.isEmptyStack())
    {
        std::cout << "3. Go Forward to the next URL" << std::endl;
    }
    std::cout << "4. Exit Browser";
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "You did not enter a number." << std::endl;
}

void codeGradeLoopFix(std::string errLocation)
{
    if (std::cin.eof())
    {
        std::cout << "There was a problem and there is no more input! @" + errLocation << std::endl;
        throw std::invalid_argument(errLocation); // return or throw an exception here to force the program to end or return from the function.
    }
}