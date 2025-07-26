/* Program name: burger.h
Author: Ty Stratton
Date last updated: 7/16/2025
Purpose: Time Program Module 6 Assignment 1, learning AVL Trees*/

#pragma once
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include "set.h"

const int TOP_NUM = 8;

enum toppingType
{
	GRILLONION,
	RAWONION,
	TOMATO,
	LETTUCE,
	BACON,
	MUSHROOM,
	PICKLE,
	NOTOP
};
const std::string toppingStr[] = {"Grilled Onion",
								  "Raw Onion",
								  "Tomato",
								  "Lettuce",
								  "Bacon",
								  "Grilled Mushroom",
								  "Pickle",
								  "None"};
const toppingType toppingList[] = {
	GRILLONION,
	RAWONION,
	TOMATO,
	LETTUCE,
	BACON,
	MUSHROOM,
	PICKLE, NOTOP};
class burger
{
public:
	burger(int numPatties);
	std::string getToppings();
	void addTopping(toppingType);
	std::string tostring();
	void setNumPatties(int num);
	int getNumPatties() const;

private:
	Set<toppingType> toppings;
	int numPatties;
};
