/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 6/30/2025
Purpose: Time Program Module 4 Assignment 1, learning backtracking*/
#include "sudoku.h"

// Set up empty grid
Sudoku::Sudoku() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

// Read puzzle from file
bool Sudoku::loadGrid(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!(file >> grid[i][j])) {
                std::cerr << "Error: Invalid data in file" << std::endl;
                file.close();
                return false;
            }
        }
    }
    
    file.close();
    return true;
}

// Check if number fits here
bool Sudoku::isValid(int row, int col, int num) const {
    // Make sure number isn't already in this row
    for (int j = 0; j < SIZE; j++) {
        if (grid[row][j] == num) {
            return false;
        }
    }
    
    // Check the column too
    for (int i = 0; i < SIZE; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }
    
    // Check the 3x3 box
    int boxStartRow = (row / 3) * 3;
    int boxStartCol = (col / 3) * 3;
    
    for (int i = boxStartRow; i < boxStartRow + 3; i++) {
        for (int j = boxStartCol; j < boxStartCol + 3; j++) {
            if (grid[i][j] == num) {
                return false;
            }
        }
    }
    
    return true;
}

// Find next empty spot
bool Sudoku::findEmptyCell(int& row, int& col) const {
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Main recursive backtracking function
bool Sudoku::solve() {
    int row, col;
    
    // No empty spots left? We're done
    if (!findEmptyCell(row, col)) {
        return true;
    }
    
    // Try each number 1-9
    for (int num = 1; num <= 9; num++) {
        if (isValid(row, col, num)) {
            // Put the number here
            grid[row][col] = num;
            
            // Try to solve the rest
            if (solve()) {
                return true;
            }
            
            // Didn't work? Take it back
            grid[row][col] = 0;
        }
    }
    
    // Nothing fits, go back
    return false;
}

// Start solving
bool Sudoku::solveGrid() {
    return solve();
}

// Make the grid look nice when printing
std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
    for (int i = 0; i < Sudoku::SIZE; i++) {
        if (i % 3 == 0 && i != 0) {
            os << "------+-------+------" << std::endl;
        }
        
        for (int j = 0; j < Sudoku::SIZE; j++) {
            if (j % 3 == 0 && j != 0) {
                os << "| ";
            }
            
            if (sudoku.grid[i][j] == 0) {
                os << ". ";
            } else {
                os << sudoku.grid[i][j] << " ";
            }
        }
        os << std::endl;
    }
    return os;
}
