#ifndef LINKED_H
#define LINKED_H
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>
#include "linkedListIterator.h"

using std::string;

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
    linkedListIterator<Type> begin();
    linkedListIterator<Type> end();

protected:
    nodeType<Type> *head;
    nodeType<Type> *tail;
    int count;

private:
    void copyList(const linkedListType<Type> &otherList);
};
template <class Type>
bool linkedListType<Type>::isEmptyList() const
{
    return (head == nullptr);
}

template <class Type>
linkedListType<Type>::linkedListType()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
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
linkedListIterator<Type> linkedListType<Type>::begin()
{
    linkedListIterator<Type> temp(head);
    return temp;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::end()
{
    linkedListIterator<Type> temp(nullptr);
    return temp;
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
        current->link;
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

#endif