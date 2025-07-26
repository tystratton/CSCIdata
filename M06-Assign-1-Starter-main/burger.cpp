/* Program name: burger.cpp
Author: Ty Stratton
Date last updated: 7/16/2025
Purpose: Time Program Module 6 Assignment 1, learning AVL Trees*/

#include "burger.h"

burger::burger(int numPatties)
{
	setNumPatties(numPatties);
}

// Builds a comma-separated string of toppings.
std::string burger::getToppings()
{
	std::string c;
	auto it = toppings.begin();
	if (it.hasNext())
	{
		c = toppingStr[it.next()];
	}
	while (it.hasNext())
	{
		c += ", " + toppingStr[it.next()];
	}
	return c;
}

// Adds a topping to the burger's set of toppings.
void burger::addTopping(toppingType topping)
{
	toppings.insert(topping);
}

// Basic validation for the number of patties.
void burger::setNumPatties(int num)
{
	if (num > 0)
		numPatties = num;
	else
		std::cout << "The number of patties should be greater than 0." << std::endl;
}

// Creates a string summary of the burger.
std::string burger::tostring()
{
	std::ostringstream out;
	out << std::setprecision(2) << std::fixed << std::showpoint;
	out << "Number of patties: " << numPatties << std::endl;
	out << "Toppings: " << getToppings();

	return out.str();
}
