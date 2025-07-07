/* Program name: stack.cpp
Author: Ty Stratton
Date last updated: 6/23/2025
Purpose: Time Program Module 3 Assignment 1, stack implementation and alias*/

#include "stack.h"

// Template alias to match test expectations
// This allows tests to use 'stack<T>' instead of 'stackType<T>'
template<typename T>
using stack = stackType<T>;

// Explicit instantiation for common types to ensure linking works
template class stackType<int>;
template class stackType<double>;
template class stackType<std::string>; 