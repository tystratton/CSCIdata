/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 6/30/2025
Purpose: Time Program Module 4 Assignment 2, learning linked lists*/

#include <iostream>
#include <fstream>
#include "unorderedLinkedList.h"
#include "product.h"

int compareDescription(product &item1, product &item2);
int comparePrice(product &item1, product &item2);
int compareRating(product &item1, product &item2);

int main()
{
    
    unorderedLinkedList<product> listByPrice;
    unorderedLinkedList<product> listByDescription;
    unorderedLinkedList<product> listByRating; 

    // Read the product information from the file
    std::ifstream infile("products.txt");
    if (!infile.is_open()) 
    {
        std::cerr << "Error opening products.txt file" << std::endl;
        return 1;
    }

    double price, rating;
    std::string description, prodNum;
    std::string line;
    
    while (std::getline(infile, line) && !line.empty())
    {
        // Read price (first line)
        price = std::stod(line);
        
        // Read description (second line)
        std::getline(infile, description);
        
        // Read product number (third line)
        std::getline(infile, prodNum);
        
        // Read rating (fourth line)
        std::getline(infile, line);
        rating = std::stod(line);
        
        // Create product and add to all three lists
        product newProduct(price, description, prodNum, rating);
        listByPrice.insert(newProduct);
        listByDescription.insert(newProduct);
        listByRating.insert(newProduct);
    }
    infile.close();

    std::cout << std::endl;
    std::cout << "original list for ordering by description: " << std::endl;
    listByDescription.print(std::cout, "\n"); // prints all of the items in the list and uses \n as the separator character.
    std::cout << std::endl
              << std::endl;
    std::cout << "original list for ordering by Price: " << std::endl;
    listByPrice.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;
    std::cout << "original list for ordering by rating" << std::endl;
    listByRating.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    // Merge sort the 3 lists
    listByDescription.mergeSort(compareDescription);
    listByPrice.mergeSort(comparePrice);
    listByRating.mergeSort(compareRating);

    std::cout << "mergeSorted by description product list: " << std::endl;
    listByDescription.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;
    std::cout << "mergeSorted by price product list: " << std::endl;
    listByPrice.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    std::cout << "mergeSorted by rating product list: " << std::endl;
    listByRating.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    return 0;
}

// Compare products by description (alphabetical order)
int compareDescription(product &item1, product &item2)
{
    std::string desc1 = item1.getDescription();
    std::string desc2 = item2.getDescription();
    
    if (desc1 < desc2)
        return -1;
    else if (desc1 > desc2)
        return 1;
    else
        return 0;
}

// Compare products by price (ascending order)
int comparePrice(product &item1, product &item2)
{
    double price1 = item1.getPrice();
    double price2 = item2.getPrice();
    
    if (price1 < price2)
        return -1;
    else if (price1 > price2)
        return 1;
    else
        return 0;
}

// Compare products by rating (ascending order)
int compareRating(product &item1, product &item2)
{
    double rating1 = item1.getRating();
    double rating2 = item2.getRating();
    
    if (rating1 < rating2)
        return -1;
    else if (rating1 > rating2)
        return 1;
    else
        return 0;
}
