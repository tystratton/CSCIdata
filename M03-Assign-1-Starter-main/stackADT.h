/* Program name: stackADT.h
Author: Ty Stratton
Date last updated: 6/23/2025
Purpose: Time Program Module 3 Assignment 1, learning stacks*/

#ifndef STACKADT_H
#define STACKADT_H

template <class type>
class stackADT
{
public:
  virtual void initializeStack() = 0;
  virtual bool isEmptyStack() const = 0;
  virtual bool isFullStack() const = 0;
  virtual void push(const type &) = 0;
  virtual type top() const = 0;
  virtual type pop() = 0;
};
#endif