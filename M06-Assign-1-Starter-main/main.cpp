/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 7/16/2025
Purpose: Time Program Module 6 Assignment 1, learning AVL Trees*/

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "burger.h"

void resetStream();
int promptNumPatties();

void promptToppings(burger &);

int main()
{
    int pat = promptNumPatties();

    burger myBurger(pat);

    promptToppings(myBurger);

    std::cout << myBurger.tostring() << std::endl;
}

// Clears the input stream on error.
void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Asks the user for the number of patties.
int promptNumPatties()
{
    int pat;
    std::cout << "How many patties do you want on your burger? ";
    std::cin >> pat;
    std::cout << std::endl;
    if (std::cin && pat > 0)
    {
        return pat;
    }
    else if (!std::cin)
    {
        resetStream();
    }
    std::cout << "You entered an invalid amount of patties. Please try again." << std::endl;

    return promptNumPatties();
}

// Asks the user to select toppings for their burger.
void promptToppings(burger &b)
{
    int topInt;
    for (int i = 0; i < 7; i++)
    {
        std::cout << "Please choose a topping from the list. Enter -1 to stop adding toppings." << std::endl;
        for (int i = 0; i < TOP_NUM; i++)
        {
            std::cout << i + 1 << ": " << toppingStr[i] << std::endl;
        }
        std::cin >> topInt;
        std::cout << std::endl;
        if (topInt == -1)
            break;
        while (!std::cin || topInt <= 0 || topInt > TOP_NUM)
        {
            if (!std::cin)
                resetStream();
            std::cout << "You did not choose a valid topping. Please try again." << std::endl;
            std::cin >> topInt;
            std::cout << std::endl;
        }
        b.addTopping(toppingList[topInt - 1]);
        if (topInt == 8)
        {
            break;
        }
    }
}
