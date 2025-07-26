#ifndef LINKED_H
#define LINKED_H
#include "stackADT.h"
#include <stdexcept>

template <class t>
struct stackNode
{
    t *data;
    stackNode<t> *link;
    ~stackNode()
    {
        delete data;
    }
};

template <class t>
class linkedStack : public stackADT<t>
{
public:
    linkedStack(int = DEFAULT_STACK_SIZE);
    linkedStack(const linkedStack<t> &);
    const linkedStack<t> &operator=(const linkedStack<t> &);
    void initializeStack();
    bool isEmptyStack() const;
    bool isFullStack() const;
    void push(const t &);
    t top() const;
    t pop();
    ~linkedStack();
    const static int DEFAULT_STACK_SIZE = 100;

private:
    void copyStack(const linkedStack<t> &);

    stackNode<t> *stackTop;
    int maxStackSize;
    int count;
};

template <class t>
linkedStack<t>::linkedStack(int stackSize)
{
    if (stackSize <= 0)
    {
        maxStackSize = DEFAULT_STACK_SIZE;
    }
    else
    {
        maxStackSize = stackSize;
    }
    stackTop = nullptr;
    count = 0;
}

template <class t>
inline linkedStack<t>::linkedStack(const linkedStack<t> &othStack)
{
    stackTop = nullptr;
    this->maxStackSize = othStack.maxStackSize;
    copyStack(othStack);
}

template <class t>
inline const linkedStack<t> &linkedStack<t>::operator=(const linkedStack<t> &othStack)
{
    this->maxStackSize = othStack.maxStackSize;
    if (this != &othStack)
    {
        copyStack(othStack);
    }
    return *this;
}

template <class t>
void linkedStack<t>::push(const t &newItem)
{
    if (isFullStack())
    {
        throw std::overflow_error("Stack Overflow. Cannot add to full stack.");
    }
    else
    {
        stackNode<t> *newNode;
        newNode = new stackNode<t>;
        newNode->data = new t(newItem);
        newNode->link = stackTop;
        stackTop = newNode;
        count++;
    }
}

template <class t>
inline t linkedStack<t>::top() const
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack");
    }
    return *(stackTop->data);
}

template <class t>
inline t linkedStack<t>::pop()
{
    stackNode<t> *temp;
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack underflow. Cannot remove from an empty stack.");
    }
    else
    {
        t newt(*(stackTop->data));
        temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
        count--;
        return newt;
    }
}

template <class t>
inline linkedStack<t>::~linkedStack()
{
    initializeStack();
}

template <class t>
inline void linkedStack<t>::copyStack(const linkedStack<t> &othStack)
{
    stackNode<t> *newNode, *current, *last;
    if (!isEmptyStack())
    {
        initializeStack();
    }
    if (othStack.isEmptyStack())
    {
        this->stackTop = nullptr;
    }
    else
    {
        current = othStack.stackTop;
        this->stackTop = new stackNode<t>;
        stackTop->data = new t(*(current->data));
        this->stackTop->link = nullptr;
        last = stackTop;
        current = current->link;
        while (current != nullptr)
        {
            newNode = new stackNode<t>;
            newNode->data = new t(*(current->data));
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
        this->count = othStack.count;
    }
}

template <class t>
inline void linkedStack<t>::initializeStack()
{
    stackNode<t> *temp;
    while (stackTop != nullptr)
    {
        temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
    }
    count = 0;
}

template <class t>
inline bool linkedStack<t>::isEmptyStack() const
{
    return stackTop == nullptr;
}

template <class t>
bool linkedStack<t>::isFullStack() const
{
    return count == maxStackSize;
}

#endif