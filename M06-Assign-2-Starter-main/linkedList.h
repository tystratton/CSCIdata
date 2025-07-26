#ifndef LINKED_H
#define LINKED_H

#include <iostream>
#include <stdexcept>
#include "linkedListIterator.h"



template <class type>
class linkedListType
{
public:
    linkedListType();
    linkedListType(const linkedListType<type> &otherList);
    const linkedListType<type> &operator=(const linkedListType<type> &);
    virtual void insert(const type &newInfo) = 0;
    virtual void deleteNode(const type &deleteItem) = 0;
    virtual bool search(const type &searchItem) const = 0;
    ~linkedListType();
    void initializeList();
    bool isEmptyList() const;
    void print(std::ostream &) const;
    int length() const;
    void destroyList();
    type *front() const;
    type *back() const;
    linkedListIterator<type> begin();
    linkedListIterator<type> end();

protected:
    nodeType<type> *head;
    nodeType<type> *tail;
    int count;

private:
    void copyList(const linkedListType<type> &otherList);
};

template <class type>
linkedListType<type>::linkedListType()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <class type>
void linkedListType<type>::initializeList()
{
    destroyList();
}

template <class type>
bool linkedListType<type>::isEmptyList() const
{
    return (head == nullptr);
}

template <class type>
void linkedListType<type>::print(std::ostream & out) const
{
    nodeType<type> * current;
    current = head;
    while(current != nullptr)
    {
        out << *(current->data) << " ";
        current = current -> link;
    }
}

template <class type>
int linkedListType<type>::length() const
{
    return count;
}

template <class type>
void linkedListType<type>::destroyList()
{
    nodeType<type> *temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->link;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

template <class type>
type * linkedListType<type>::front() const
{
    if(this->isEmptyList())
        throw std::out_of_range("Cannot get first item of an empty list");
    return head->data;
}

template <class type>
type *linkedListType<type>::back() const
{
    if(this->isEmptyList())
        throw std::out_of_range("Cannot get last item of an empty list");
    return tail->data;
}

template <class type>
linkedListType<type>::linkedListType(const linkedListType<type> &otherList)
{
    head = nullptr;
    copyList(otherList);
}

template<class type>
const linkedListType<type>& linkedListType<type>::operator=(const linkedListType<type> & otherList)
{
    if(this != &otherList)
    {
        copyList(otherList);
    }
    return *this;
}

template <class type>
linkedListType<type>::~linkedListType()
{
    destroyList();
}

template <class type>
void linkedListType<type>::copyList(const linkedListType<type> &otherList)
{
    nodeType<type> *newNode;
    nodeType<type> *current;
    if(!this->isEmptyList())
    {
        this->destroyList();
    }
    if(otherList.isEmptyList())
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    else
    {
        current = otherList.head;
        count = otherList.count;
        this->head = new nodeType<type>;
        head->data = new type(*(current->data));
        head->link = nullptr;
        tail = head;
        current = current->link;
        while(current != nullptr)
        {
            newNode = new nodeType<type>;
            newNode->data = new type(*(current->data));
            newNode->link = nullptr;
            tail->link = newNode;
            current = current->link;
        }
    }
}

template <class type>
linkedListIterator<type> linkedListType<type>::begin()
{
    linkedListIterator<type> temp(head);
    return temp;
}

template <class type>
linkedListIterator<type> linkedListType<type>::end()
{
    linkedListIterator<type> temp(nullptr);
    return temp;
}

#endif