#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "binarySearchTree.h"
#include "product.h"

void displayMenu();

int main()
{
    bSearchTreeType<product> productTree;
    std::ifstream infile("products.txt");
    if (!infile)
    {
        std::cerr << "Error opening products.txt" << std::endl;
        return 1;
    }

    double price, rating;
    std::string description, prodNum, line;

    while (infile >> price)
    {
        // getline needs to consume the rest of the line after reading price
        std::getline(infile, line); 
        std::getline(infile, description);
        infile >> prodNum;
        infile >> rating;
        std::getline(infile, line); // consume rest of line

        product p(price, description, prodNum, rating);
        productTree.insert(p);
    }

    infile.close();

    int choice;
    do
    {
        displayMenu();
        std::cin >> choice;
        // handle non-integer input
        while(std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayMenu();
            std::cin >> choice;
        }


        if (choice == 1)
        {
            std::cout << "Enter product number to search for: ";
            std::cin >> prodNum;
            product dummy(1.0, "", prodNum);
            product foundProduct(1.0, "", "dummy");

            if (productTree.find(dummy, foundProduct))
            {
                std::cout << "Product found: " << std::endl;
                std::cout << foundProduct << std::endl;
            }
            else
            {
                std::cout << prodNum << " is not found in the tree." << std::endl;
            }
        }
        else if (choice == 2)
        {
            std::cout << "Enter product number to delete: ";
            std::cin >> prodNum;
            product dummy(1.0, "", prodNum);
            productTree.deleteNode(dummy);
        }
    } while (choice != 3);

    std::cout << "\nIn-order traversal of the product tree:\n"
              << std::endl;
    productTree.inorderTraversal();

    return 0;
}

void displayMenu()
{
    std::cout << "\nMenu:\n";
    std::cout << "1. Search for a product\n";
    std::cout << "2. Delete a product\n";
    std::cout << "3. Quit\n";
    std::cout << "Enter your choice: ";
}
