/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 6/30/2025
Purpose: Time Program Module 4 Assignment 1, learning backtracking*/

#include <iostream>
#include "sudoku.h"

using namespace std;

int main() {
    // Make a new puzzle
    Sudoku puzzle;
    
    // Load puzzle from file
    cout << "Loading Sudoku puzzle from sudoku.txt..." << endl;
    if (!puzzle.loadGrid("sudoku.txt")) {
        cout << "Failed to load puzzle from file!" << endl;
        return 1;
    }
    
    // Show the puzzle
    cout << "\nStarting Sudoku puzzle:" << endl;
    cout << puzzle << endl;
    
    // Try to solve it
    cout << "Solving puzzle using backtracking..." << endl;
    if (puzzle.solveGrid()) {
        cout << "\nPuzzle solved successfully!" << endl;
        cout << "\nSolved Sudoku puzzle:" << endl;
        cout << puzzle << endl;
    } else {
        cout << "\nNo solution exists for this puzzle!" << endl;
    }
    
    return 0;
}
