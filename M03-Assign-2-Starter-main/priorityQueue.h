/* Program name: priorityQueue.h
Author: Ty Stratton
Date last updated: 6/23/2025
Purpose: Time Program Module 3 Assignment 2, learning priority queues*/

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "BugReport.h"

using std::string;

// Node structure for linked lists
template <class Type>
struct nodeType
{
    Type *info;
    nodeType<Type> *link;
    ~nodeType()
    {
        delete info;
    }
};

// Base linked list functionality for unorderedLinkedList
template <class Type>
class linkedListType
{
public:
    linkedListType();
    linkedListType(const linkedListType<Type> &otherList);
    const linkedListType<Type> &operator=(const linkedListType<Type> &);
    virtual void insert(const Type &newInfo) = 0;
    virtual void deleteNode(const Type &deleteItem) = 0;
    virtual bool search(const Type &searchItem) const = 0;
    ~linkedListType();
    void initializeList();
    bool isEmptyList() const;
    string print() const;
    int length() const;
    void destroyList();
    Type *front() const;
    Type *back() const;

protected:
    nodeType<Type> *head;
    nodeType<Type> *tail;
    int count;

private:
    void copyList(const linkedListType<Type> &otherList);
};

template <class Type>
linkedListType<Type>::linkedListType()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <class Type>
bool linkedListType<Type>::isEmptyList() const
{
    return (head == nullptr);
}

template <class Type>
void linkedListType<Type>::destroyList()
{
    nodeType<Type> *temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->link;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

template <class Type>
void linkedListType<Type>::initializeList()
{
    destroyList();
}

template <class Type>
string linkedListType<Type>::print() const
{
    std::ostringstream out;
    nodeType<Type> *current;
    current = head;
    while (current != nullptr)
    {
        out << *(current->info) << std::endl;
        current = current->link;
    }
    return out.str();
}

template <class Type>
int linkedListType<Type>::length() const
{
    return count;
}

template <class Type>
Type *linkedListType<Type>::front() const
{
    if (this->isEmptyList())
        throw std::out_of_range("Cannot get first item of an empty list");
    return head->info;
}

template <class Type>
Type *linkedListType<Type>::back() const
{
    if (this->isEmptyList())
        throw std::out_of_range("Cannot get last item of an empty list");
    return tail->info;
}

template <class Type>
void linkedListType<Type>::copyList(const linkedListType<Type> &otherList)
{
    nodeType<Type> *newNode;
    nodeType<Type> *current;
    if (!this->isEmptyList())
    {
        destroyList();
    }
    if (otherList.isEmptyList())
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    else
    {
        current = otherList.head;
        count = otherList.count;
        this->head = new nodeType<Type>;
        head->info = new Type(*(current->info));
        head->link = nullptr;
        tail = head;
        current = current->link;
        while (current != nullptr)
        {
            newNode = new nodeType<Type>;
            newNode->info = new Type(*(current->info));
            newNode->link = nullptr;
            tail->link = newNode;
            tail = newNode;
            current = current->link;
        }
    }
}

template <class Type>
linkedListType<Type>::~linkedListType()
{
    destroyList();
}

template <class Type>
linkedListType<Type>::linkedListType(const linkedListType<Type> &otherList)
{
    head = nullptr;
    copyList(otherList);
}

template <class Type>
const linkedListType<Type> &linkedListType<Type>::operator=(const linkedListType<Type> &otherList)
{
    if (this != &otherList)
    {
        copyList(otherList);
    }
    return *this;
}

// Unordered Linked List class
template <class Type>
class unorderedLinkedList: public linkedListType<Type>
{
public:
    bool search(const Type& searchItem) const;
    void insert(const Type& newItem);
    void deleteNode(const Type& deleteItem);
};

template <class Type>
bool unorderedLinkedList<Type>::search(const Type& searchItem) const
{
    nodeType<Type> * current;
    bool found = false;
    current = this->head;
    while(current != nullptr && !found)
    {
        if(*(current->info) == searchItem)
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

template <class Type>
void unorderedLinkedList<Type>::insert(const Type& newItem)
{
    nodeType<Type> * newNode;
    newNode = new nodeType<Type>;
    newNode->info = new Type(newItem);
    newNode->link = nullptr;
    if(this->isEmptyList())
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

template <class Type>
void unorderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
    nodeType<Type> * current;
    nodeType<Type> * trailCurrent;
    bool found;
    
    if(this->head == nullptr)
        throw std::out_of_range("Cannot delete from empty list.");
    else
    {
        if(*(this->head->info) == deleteItem)
        {
            current = this->head;
            this->head = this->head->link;
            this->count--;
            if(this->head == nullptr)
                this->tail = nullptr;
            delete current;
        }
        else 
        {
            found = false;
            trailCurrent = this->head;
            current = this->head->link;
            while(current != nullptr && !found)
            {
                if(*(current->info) != deleteItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                    found = true;
            }
            if(found)
            {
                trailCurrent->link = current->link;
                this->count--;
                if(this->tail == current)
                    this->tail = trailCurrent;
                delete current;
            }
            else 
                throw std::out_of_range("Item not found in list. Cannot delete.");
        }
    }
}

// Priority Queue class - standalone implementation
template <class Type>
class priorityQueue
{
public:
    priorityQueue();
    ~priorityQueue();
    void insert(const Type& newItem);
    void deleteNode(const Type& deleteItem);
    bool search(const Type& searchItem) const;
    Type front() const;
    Type back() const;
    void dequeue();
    bool isEmptyList() const;
    string print() const;
    void destroyList();

private:
    nodeType<Type>* head;
    nodeType<Type>* tail;
    int count;
};

template <class Type>
priorityQueue<Type>::priorityQueue()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <class Type>
priorityQueue<Type>::~priorityQueue()
{
    destroyList();
}

template <class Type>
bool priorityQueue<Type>::isEmptyList() const
{
    return (head == nullptr);
}

template <class Type>
void priorityQueue<Type>::destroyList()
{
    nodeType<Type> *temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->link;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

template <class Type>
string priorityQueue<Type>::print() const
{
    std::ostringstream out;
    nodeType<Type> *current;
    current = head;
    while (current != nullptr)
    {
        out << *(current->info) << std::endl;
        current = current->link;
    }
    return out.str();
}

template <class Type>
void priorityQueue<Type>::insert(const Type &newItem)
{
    nodeType<Type> *newNode;      //pointer to create a node
    nodeType<Type> *current;      //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    bool found;

    newNode = new nodeType<Type>; //create the node
    newNode->info = new Type(newItem);
    newNode->link = nullptr; //set the link field of newNode to nullptr

    if (head == nullptr) //if list is empty, newNode is the only node
    {
        head = newNode;
        tail = newNode;
        count++;
    }
    else
    {
        //if the new item is bigger than the first item
        if (newItem > *(head->info))
        {
            newNode->link = head;
            head = newNode;
            count++;
        }
        else
        {
            trailCurrent = head;
            current = head->link;
            found = false;

            while (current != nullptr && !found)
            {
                if (*(current->info) >= newItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                    found = true;
            }

            trailCurrent->link = newNode;
            newNode->link = current;

            if (current == nullptr)
                tail = newNode;

            count++;
        }
    }
}

template <class Type>
void priorityQueue<Type>::deleteNode(const Type &deleteItem)
{
    nodeType<Type> *current;      //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    bool found;

    if (head == nullptr) //Case 1; the list is empty.
        throw std::out_of_range("Cannot delete from an empty list.");
    else
    {
        if (*(head->info) == deleteItem) //Case 2
        {
            current = head;
            head = head->link;
            count--;
            if (head == nullptr) //the list has only one node
                tail = nullptr;
            delete current;
        }
        else //search the list for the node with the given info
        {
            found = false;
            trailCurrent = head;      //set trailCurrent to point to the first node
            current = head->link; //set current to point to the second node

            while (current != nullptr && !found)
            {
                if (*(current->info) != deleteItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                    found = true;
            } //end while

            if (found) //Case 3; if found, delete the node
            {
                trailCurrent->link = current->link;
                count--;

                if (tail == current)   //node to be deleted was the last node
                    tail = trailCurrent; //update the value of tail
                delete current;              //delete the node from the list
            }
            else
                throw std::out_of_range("The item to be deleted is not in the list.");
        }
    }
}

template <class Type>
bool priorityQueue<Type>::search(const Type &searchItem) const
{
    nodeType<Type> *current; //pointer to traverse the list
    bool found = false;

    current = head; //set current to point to the first node in the list

    while (current != nullptr && !found) //search the list
        if (*(current->info) == searchItem) //searchItem is found
            found = true;
        else
            current = current->link; //move current to the next node
    return found;
}

template <class Type>
Type priorityQueue<Type>::front() const
{
    if (isEmptyList())
        throw std::out_of_range("Cannot get the front of an empty queue.");
    return *(head->info);
}

template <class Type>
Type priorityQueue<Type>::back() const
{
    if (isEmptyList())
        throw std::out_of_range("Cannot get the back of an empty queue.");
    return *(tail->info);
}

template <class Type>
void priorityQueue<Type>::dequeue()
{
    nodeType<Type> *temp;
    if (!isEmptyList())
    {
        temp = head;
        head = head->link;
        delete temp;
        count--;
        if (head == nullptr)
        {
            tail = nullptr;
        }
    }
}

#endif
