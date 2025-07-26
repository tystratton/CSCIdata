/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 7/17/2025
Purpose: Time Program Module 7 Assignment 1, learning Hash Tables*/

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "hashTable.h"

using namespace std;

int main() {
    // Create both hash table types
    HashTableQuadratic htQuadratic;
    HashTableChaining htChaining;

    cout << "Reading numbers from input.txt and inserting into hash tables..." << endl;

    // Open the input file
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error opening input.txt" << endl;
        return 1;
    }

    // Read all numbers into a vector
    int number;
    vector<int> numbers;
    while (inputFile >> number) {
        numbers.push_back(number);
    }
    inputFile.close();

    // Time the quadratic probing insertions
    auto start = chrono::high_resolution_clock::now();
    for (int num : numbers) {
        htQuadratic.insert(num);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> quadraticInsertTime = end - start;

    // Time the chaining insertions  
    start = chrono::high_resolution_clock::now();
    for (int num : numbers) {
        htChaining.insert(num);
    }
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> chainingInsertTime = end - start;

    // Display insertion results
    cout << "--- Insertion Results ---" << endl;
    cout << "Quadratic Probing:" << endl;
    cout << "  - Insertion time: " << quadraticInsertTime.count() << " seconds" << endl;
    cout << "  - Collisions: " << htQuadratic.getCollisions() << endl;

    cout << "Separate Chaining:" << endl;
    cout << "  - Insertion time: " << chainingInsertTime.count() << " seconds" << endl;
    cout << "  - Collisions: " << htChaining.getCollisions() << endl;
    cout << endl;

    // Interactive search loop
    int valueToSearch;
    while (true) {
        cout << "Enter a number to search for (-1 to exit): ";
        cin >> valueToSearch;

        if (valueToSearch == -1) {
            break;
        }

        cout << "\n--- Search Results for " << valueToSearch << " ---" << endl;
        
        // Test quadratic probing search speed
        start = chrono::high_resolution_clock::now();
        bool foundQuadratic = htQuadratic.search(valueToSearch);
        end = chrono::high_resolution_clock::now();
        chrono::duration<double> quadraticSearchTime = end - start;
        cout << "Quadratic Probing:" << endl;
        cout << "  - Found: " << (foundQuadratic ? "Yes" : "No") << endl;
        cout << "  - Search time: " << quadraticSearchTime.count() * 1e9 << " nanoseconds" << endl;

        // Test chaining search speed
        start = chrono::high_resolution_clock::now();
        bool foundChaining = htChaining.search(valueToSearch);
        end = chrono::high_resolution_clock::now();
        chrono::duration<double> chainingSearchTime = end - start;
        cout << "Separate Chaining:" << endl;
        cout << "  - Found: " << (foundChaining ? "Yes" : "No") << endl;
        cout << "  - Search time: " << chainingSearchTime.count() * 1e9 << " nanoseconds" << endl;
        cout << endl;
    }

    return 0;
}
