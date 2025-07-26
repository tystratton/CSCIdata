#ifndef UNORDERED_H
#define UNORDERED_H
#include "linkedList.h"

template <class type>
class unorderedLinkedList : public linkedListType<type>
{
public:
    void insert(const type &newInfo);
    void deleteNode(const type &deleteItem);
    bool search(const type &searchItem) const;
    std::string print() const;
};

template <class type>
std::string unorderedLinkedList<type>::print() const
{
    std::ostringstream out;
    nodeType<type> *current;
    current = this->head;
    while (current != nullptr)
    {
        out << *(current->data) << " ";
        current = current->link;
    }
    return out.str();
}

template <class type>
void unorderedLinkedList<type>::insert(const type &newInfo)
{
    nodeType<type> *newNode;
    newNode = new nodeType<type>;
    newNode->data = new type(newInfo);
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
void unorderedLinkedList<type>::deleteNode(const type &deleteItem)
{
    nodeType<type> * current;
    nodeType<type> * trailCurrent;
    bool found;
    if(this->isEmptyList())
        throw std::out_of_range("Cannot delete from empty list.");
    else
    {
        if(*(this->head->data) == deleteItem)
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
                if(*(current->data) != deleteItem)
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
template <class type>
bool unorderedLinkedList<type>::search(const type &searchItem) const
{
    nodeType<type> * current;
    bool found = false;
    current = this->head;
    while(current != nullptr && !found)
    {
        if(*(current->data) == searchItem)
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

#endif