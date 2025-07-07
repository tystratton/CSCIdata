#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"
#include <iostream>

template <class elemType>
class bSearchTreeType : public binaryTreeType<elemType>
{
public:
    bool search(const elemType &searchItem) const;
    void insert(const elemType &insertItem);
    void deleteNode(const elemType &deleteItem);
    bool find(const elemType &searchItem, elemType &foundItem) const;

private:
    void deleteFromTree(nodeType<elemType> *&p);
};

template <class elemType>
bool bSearchTreeType<elemType>::search(const elemType &searchItem) const
{
    nodeType<elemType> *current;
    bool found = false;

    if (this->root == nullptr)
        return false;
    else
    {
        current = this->root;
        while (current != nullptr && !found)
        {
            if (*(current->info) == searchItem)
                found = true;
            else if (*(current->info) > searchItem)
                current = current->lLink;
            else
                current = current->rLink;
        }
    }
    return found;
}
template <class elemType>
bool bSearchTreeType<elemType>::find(const elemType &searchItem, elemType &foundItem) const
{
    nodeType<elemType> *current;
    bool found = false;

    if (this->root == nullptr)
        return false;
    else
    {
        current = this->root;
        while (current != nullptr && !found)
        {
            if (*(current->info) == searchItem)
            {
                found = true;
                foundItem = *(current->info);
            }
            else if (*(current->info) > searchItem)
                current = current->lLink;
            else
                current = current->rLink;
        }
    }
    return found;
}
template <class elemType>
void bSearchTreeType<elemType>::insert(const elemType &insertItem)
{
    nodeType<elemType> *current;
    nodeType<elemType> *trailCurrent = nullptr;
    nodeType<elemType> *newNode;

    newNode = new nodeType<elemType>;
    newNode->info = new elemType(insertItem);
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;

    if (this->root == nullptr)
        this->root = newNode;
    else
    {
        current = this->root;

        while (current != nullptr)
        {
            trailCurrent = current;
            if (*(current->info) == insertItem)
            {
                std::cerr << "The item to be inserted is already in the tree. Duplicates are not allowed." << std::endl;
                delete newNode->info;
                delete newNode;
                return;
            }
            else if (*(current->info) > insertItem)
                current = current->lLink;
            else
                current = current->rLink;
        }

        if (*(trailCurrent->info) > insertItem)
            trailCurrent->lLink = newNode;
        else
            trailCurrent->rLink = newNode;
    }
}

template <class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType &deleteItem)
{
    nodeType<elemType> *current;
    nodeType<elemType> *trailCurrent;
    bool found = false;

    if (this->root == nullptr)
    {
        std::cout << "Cannot delete from an empty tree." << std::endl;
        return;
    }

    current = this->root;
    trailCurrent = this->root;

    while (current != nullptr && !found)
    {
        if (*(current->info) == deleteItem)
            found = true;
        else
        {
            trailCurrent = current;
            if (*(current->info) > deleteItem)
                current = current->lLink;
            else
                current = current->rLink;
        }
    }

    if (current == nullptr)
        std::cout << deleteItem.getProdNum() << " is not in the tree." << std::endl;
    else if (found)
    {
        if (current == this->root)
            deleteFromTree(this->root);
        else if (*(trailCurrent->info) > deleteItem)
            deleteFromTree(trailCurrent->lLink);
        else
            deleteFromTree(trailCurrent->rLink);
    }
}

template <class elemType>
void bSearchTreeType<elemType>::deleteFromTree(nodeType<elemType> *&p)
{
    nodeType<elemType> *current;
    nodeType<elemType> *trailCurrent;
    nodeType<elemType> *temp;

    if (p == nullptr)
        std::cerr << "Error: The node to be deleted is null." << std::endl;
    else if (p->lLink == nullptr && p->rLink == nullptr)
    {
        temp = p;
        p = nullptr;
        delete temp;
    }
    else if (p->lLink == nullptr)
    {
        temp = p;
        p = p->rLink;
        delete temp;
    }
    else if (p->rLink == nullptr)
    {
        temp = p;
        p = p->lLink;
        delete temp;
    }
    else
    {
        current = p->lLink;
        trailCurrent = nullptr;

        while (current->rLink != nullptr)
        {
            trailCurrent = current;
            current = current->rLink;
        }

        *(p->info) = *(current->info);

        if (trailCurrent == nullptr)
            p->lLink = current->lLink;
        else
            trailCurrent->rLink = current->lLink;

        delete current;
    }
}

#endif