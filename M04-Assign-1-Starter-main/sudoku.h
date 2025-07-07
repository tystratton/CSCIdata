/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 6/30/2025
Purpose: Time Program Module 4 Assignment 1, learning backtracking*/

#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <fstream>
#include <string>

class Sudoku {
private:
    static const int SIZE = 9;
    int grid[SIZE][SIZE];
    
    // Helper functions
    bool isValid(int row, int col, int num) const;
    bool findEmptyCell(int& row, int& col) const;
    bool solve();

public:
    // Constructor
    Sudoku();
    
    // Load puzzle from file
    bool loadGrid(const std::string& filename);
    
    // Solve using backtracking
    bool solveGrid();
    
    // For printing the grid
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
};

#endif
