/* Program name: stack.h
Author: Ty Stratton
Date last updated: 6/23/2025
Purpose: Time Program Module 3 Assignment 1, learning stacks*/

#ifndef H_StackType
#define H_StackType

#include <iostream>
#include <stdexcept>
#include "stackADT.h"

template <class Type>
class stackType : public stackADT<Type>
{
public:
    const stackType<Type> &operator=(const stackType<Type> &);
    void initializeStack();
    bool isEmptyStack() const;
    bool isFullStack() const;
    void push(const Type &newItem);
    Type top() const;
    Type pop();
    stackType(int stackSize = 100);
    stackType(const stackType<Type> &otherStack);
    ~stackType();

private:
    int maxStackSize;
    int stackTop;
    Type **list;
    void copyStack(const stackType<Type> &otherStack);
};

template <class Type>
void stackType<Type>::initializeStack()
{
    for (int i = 0; i < stackTop; i++)
    {
        delete list[i];
        list[i] = nullptr;
    }
    stackTop = 0;
}

template <class Type>
bool stackType<Type>::isEmptyStack() const
{
    return (stackTop == 0);
}

template <class Type>
bool stackType<Type>::isFullStack() const
{
    return (stackTop == maxStackSize);
}

template <class Type>
void stackType<Type>::push(const Type &newItem)
{
    if (isFullStack())
    {
        throw std::overflow_error("Stack is full. Cannot add element.");
    }
    list[stackTop] = new Type(newItem);
    stackTop++;
}

template <class Type>
Type stackType<Type>::top() const
{
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack is empty. Cannot read top element.");
    }
    return *list[stackTop - 1];
}

template <class Type>
Type stackType<Type>::pop()
{
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack is empty. Cannot pop element.");
    }
    stackTop--;
    Type item = *list[stackTop];
    delete list[stackTop];
    list[stackTop] = nullptr;
    return item;
}

template <class Type>
stackType<Type>::stackType(int stackSize)
{
    if (stackSize <= 0)
    {
        std::cout << "Size of the array to hold the stack must be positive." << std::endl;
        std::cout << "Creating an array of size 100." << std::endl;
        maxStackSize = 100;
    }
    else
    {
        maxStackSize = stackSize;
    }
    stackTop = 0;
    list = new Type *[maxStackSize];
}

template <class Type>
stackType<Type>::~stackType()
{
    for (int i = 0; i < stackTop; i++)
    {
        delete list[i];
    }
    delete[] list;
}

template <class Type>
void stackType<Type>::copyStack(const stackType<Type> &otherStack)
{
    if (list != nullptr)
    {
        for (int i = 0; i < stackTop; i++)
        {
            delete list[i];
        }
        delete[] list;
    }

    maxStackSize = otherStack.maxStackSize;
    stackTop = otherStack.stackTop;
    list = new Type *[maxStackSize];

    for (int j = 0; j < stackTop; j++)
    {
        list[j] = new Type(*(otherStack.list[j]));
    }
}

template <class Type>
stackType<Type>::stackType(const stackType<Type> &otherStack)
{
    list = nullptr;
    stackTop = 0;
    copyStack(otherStack);
}

template <class Type>
const stackType<Type> &stackType<Type>::operator=(const stackType<Type> &otherStack)
{
    if (this != &otherStack)
    {
        copyStack(otherStack);
    }
    return *this;
}

// Template alias to match test expectations
template<typename T>
using stack = stackType<T>;

#endif