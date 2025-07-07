/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 6/30/2025
Purpose: Time Program Module 4 Assignment 2, learning linked lists*/

#ifndef UNORDERED_H
#define UNORDERED_H
#include "linkedList.h"

template <class type>
class unorderedLinkedList : public linkedListType<type>
{
public:
    void insert(const type &newdata);
    void deleteNode(const type &deleteItem);
    bool search(const type &searchItem) const;
    void mergeSort(int (*compare)(type &, type &));

private:
    void mergeSortHelper(node<type> **headRef, int (*compare)(type &, type &));
    node<type>* merge(node<type> *first, node<type> *second, int (*compare)(type &, type &));
    void split(node<type> *source, node<type> **front, node<type> **back);
};

template <class type>
inline void unorderedLinkedList<type>::insert(const type &newdata)
{
    node<type> *newNode;
    newNode = new node<type>;
    newNode->data = new type(newdata);
    newNode->link = nullptr;

    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
        this->count++;
    }
    else
    {
        this->tail->link = newNode;
        this->tail = newNode;
        this->count++;
    }
}

template <class type>
inline void unorderedLinkedList<type>::deleteNode(const type &deleteItem)
{
    node<type> *current;
    node<type> *trailCurrent;
    bool found;
    if (this->isEmptyList())
        throw std::out_of_range("Cannot delete from empty list.");
    else
    {
        if (*(this->head->data) == deleteItem)
        {
            current = this->head;
            this->head = this->head->link;
            this->count--;
            if (this->head == nullptr)
                this->tail = nullptr;
            delete current;
        }
        else
        {
            found = false;
            trailCurrent = this->head;
            current = this->head->link;
            while (current != nullptr && !found)
            {
                if (*(current->data) != deleteItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                    found = true;
            }
            if (found)
            {
                trailCurrent->link = current->link;
                this->count--;
                if (this->tail == current)
                    this->tail = trailCurrent;
                delete current;
            }
            else
                throw std::out_of_range("Item not found in list. Cannot delete.");
        }
    }
}

template <class type>
inline bool unorderedLinkedList<type>::search(const type &searchItem) const
{
    node<type> *current;
    bool found = false;
    current = this->head;
    while (current != nullptr && !found)
    {
        if (*(current->data) == searchItem)
        {
            found = true;
        }
        else
        {
            current = current->link;
        }
    }
    return found;
}

template <class type>
void unorderedLinkedList<type>::mergeSort(int (*compare)(type &, type &))
{
    if (this->head != nullptr)
    {
        mergeSortHelper(&(this->head), compare);
        
        // Now we need to fix the tail pointer since merge sort might have changed our list structure
        node<type> *current = this->head;
        while (current->link != nullptr)
        {
            current = current->link;
        }
        this->tail = current;
    }
}

template <class type>
void unorderedLinkedList<type>::mergeSortHelper(node<type> **headRef, int (*compare)(type &, type &))
{
    node<type> *head = *headRef;
    node<type> *first;
    node<type> *second;
    
    // If we've got nothing or just one item, we're already sorted
    if ((head == nullptr) || (head->link == nullptr))
    {
        return;
    }
    
    // Split the list into two halves
    split(head, &first, &second);
    
    // Recursively sort both halves
    mergeSortHelper(&first, compare);
    mergeSortHelper(&second, compare);
    
    // Merge the sorted halves
    *headRef = merge(first, second, compare);
}

template <class type>
node<type>* unorderedLinkedList<type>::merge(node<type> *first, node<type> *second, int (*compare)(type &, type &))
{
    node<type> *result = nullptr;
    
    // Handle the easy cases first - if one list is empty, just return the other
    if (first == nullptr)
        return second;
    if (second == nullptr)
        return first;
    
    // Pick either first or second, and recur
    if (compare(*(first->data), *(second->data)) <= 0)
    {
        result = first;
        result->link = merge(first->link, second, compare);
    }
    else
    {
        result = second;
        result->link = merge(first, second->link, compare);
    }
    
    return result;
}

template <class type>
void unorderedLinkedList<type>::split(node<type> *source, node<type> **front, node<type> **back)
{
    node<type> *fast;
    node<type> *slow;
    
    slow = source;
    fast = source->link;
    
    // Move fast two nodes and slow one node
    while (fast != nullptr)
    {
        fast = fast->link;
        if (fast != nullptr)
        {
            slow = slow->link;
            fast = fast->link;
        }
    }
    
    // slow is before the midpoint, so split it in two
    *front = source;
    *back = slow->link;
    slow->link = nullptr;
}

#endif