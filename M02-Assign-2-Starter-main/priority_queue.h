#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "orderedLinkedList.h"
#include "bug_report.h" // Include for BugReport type

template <class Type>
class PriorityQueue : private orderedLinkedList<Type>
{
public:
    void enqueue(const Type &item);
    Type dequeue();
    bool isEmpty() const;
    void print() const;
};

template <class Type>
void PriorityQueue<Type>::enqueue(const Type &item)
{
    this->insert(item);
}

template <class Type>
Type PriorityQueue<Type>::dequeue()
{
    if (this->isEmpty())
    {
        throw std::underflow_error("Queue is empty.");
    }
    Type item = this->front();
    this->deleteNode(item);
    return item;
}

template <class Type>
bool PriorityQueue<Type>::isEmpty() const
{
    return this->isEmptyList();
}

template <class Type>
void PriorityQueue<Type>::print() const
{
    this->printList();
}

#endif // PRIORITY_QUEUE_H 