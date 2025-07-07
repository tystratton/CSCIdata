/* Program name: orderedLinkedList.h
Author: Ty Stratton
Date last updated: 6/16/2025
Purpose: Time Program Module 2 Assignment 2, learning linked lists*/

#ifndef OLLIST_H
#define OLLIST_H

#include "linkedList.h"

template <class Type>
class orderedLinkedList : public linkedList<Type> {
public:
    // Implement pure virtual functions from base class
    bool search(const Type& searchItem) const override;
    void insertFirst(const Type& newItem) override;
    void insertLast(const Type& newItem) override;
    void deleteNode(const Type& deleteItem) override;
    
    // The main method you need to implement for ordering
    void insert(const Type& newItem);
};

// Implementation of pure virtual functions
template <class Type>
bool orderedLinkedList<Type>::search(const Type& searchItem) const {
    node<Type>* current = this->first;
    while (current != nullptr && *(current->info) < searchItem) {
        current = current->link;
    }
    return (current != nullptr && *(current->info) == searchItem);
}

template <class Type>
void orderedLinkedList<Type>::insertFirst(const Type& newItem) {
    insert(newItem); // Use insert to maintain order
}

template <class Type>
void orderedLinkedList<Type>::insertLast(const Type& newItem) {
    insert(newItem); // Use insert to maintain order
}

template <class Type>
void orderedLinkedList<Type>::deleteNode(const Type& deleteItem) {
    node<Type>* current = this->first;
    node<Type>* trailCurrent = nullptr;
    
    // Find the node to delete
    while (current != nullptr && *(current->info) != deleteItem) {
        trailCurrent = current;
        current = current->link;
    }
    
    if (current != nullptr) { // Node found
        this->count--;
        
        if (this->first == current) { // Delete first node
            this->first = this->first->link;
            if (this->first == nullptr)
                this->last = nullptr;
        } else {
            trailCurrent->link = current->link;
            if (current == this->last)
                this->last = trailCurrent;
        }
        
        delete current;
    }
}

template <class Type>
void orderedLinkedList<Type>::insert(const Type& newItem) {
    node<Type>* newNode = new node<Type>;
    newNode->info = new Type(newItem);
    newNode->link = nullptr;
    
    node<Type>* current = this->first;
    node<Type>* trailCurrent = nullptr;
    
    // Find the correct position to insert
    while (current != nullptr && *(current->info) < newItem) {
        trailCurrent = current;
        current = current->link;
    }
    
    if (trailCurrent == nullptr) { // Insert at beginning
        newNode->link = this->first;
        this->first = newNode;
        if (this->last == nullptr)
            this->last = newNode;
    } else { // Insert after trailCurrent
        newNode->link = current;
        trailCurrent->link = newNode;
        if (current == nullptr)
            this->last = newNode;
    }
    
    this->count++;
}

#endif