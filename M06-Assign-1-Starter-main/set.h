/* Program name: set.h
Author: Ty Stratton
Date last updated: 7/16/2025
Purpose: Time Program Module 6 Assignment 1, learning AVL Trees*/

#ifndef SET_H
#define SET_H
#include "AVLTree.h"

template <class T>
class Set
{
public:
    // Add an item to the set.
    void insert(const T &item) { tree.insert(item); }
    // Get an iterator to the beginning of the set.
    typename AVLTree<T>::Iterator begin() { return tree.begin(); }

private:
    AVLTree<T> tree;
};

#endif