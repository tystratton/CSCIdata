#ifndef AVLTREE_H
#define AVLTREE_H

#include "binarySearchTree.h"
#include <sstream>
#include <stack>

template <class T>
class AVLTree : public binarySearchTree<T>
{
public:
    void insert(const T &insertItem);
    // void deleteNode(const T &deleteItem); // complete for bonus points (5pts)

    class Iterator
    {
    public:
        Iterator(binaryNode<T> *root);

        bool hasNext();
        T next();

    private:
        std::stack<binaryNode<T> *> nodeStack;
        void pushLeftNodes(binaryNode<T> *node);
    };

    Iterator begin() { return Iterator(this->getRoot()); }

private:
    void rotateToLeft(binaryNode<T> *&root);
    void rotateToRight(binaryNode<T> *&root);
    void balanceFromLeft(binaryNode<T> *&root);
    void balanceFromRight(binaryNode<T> *&root);
    void insertIntoAVL(binaryNode<T> *&root, binaryNode<T> *newNode, bool &isTaller);
};

template <class T>
inline void AVLTree<T>::insert(const T &insertItem)
{
    bool isTaller = false;
    binaryNode<T> *newNode = new binaryNode<T>;
    newNode->data = new T(insertItem);
    newNode->bfactor = 0;
    newNode->height = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;
    insertIntoAVL(this->getRoot(), newNode, isTaller);
}

template <class T>
inline void AVLTree<T>::rotateToLeft(binaryNode<T> *&root)
{
    binaryNode<T> *p;
    if (root == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    else if (root->right == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    else
    {
        p = root->right;
        root->right = p->left;
        p->left = root;
        root = p;
    }
}

template <class T>
inline void AVLTree<T>::rotateToRight(binaryNode<T> *&root)
{
    binaryNode<T> *p;
    if (root == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    else if (root->left == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    else
    {
        p = root->left;
        root->left = p->right;
        p->right = root;
        root = p;
    }
}

template <class T>
inline void AVLTree<T>::balanceFromLeft(binaryNode<T> *&root)
{
    binaryNode<T> *p;
    binaryNode<T> *w;
    p = root->left;
    switch (p->bfactor)
    {
    case -1: // left high
        root->bfactor = 1;
        p->bfactor = 0;
        rotateToRight(root);
        break;
    case 0: // even high
        throw std::runtime_error("Left subtree is balanced.");
    case 1: // right high
        w = p->right;
        switch (w->bfactor)
        {
        case -1:
            root->bfactor = 0;
            p->bfactor = 0;
            break;
        case 0:
            root->bfactor = 0;
            p->bfactor = 0;
        case 1:
            root->bfactor = 0;
            p->bfactor = -1;
        }
        w->bfactor = 0;
        rotateToLeft(p);
        root->left = p;
        rotateToRight(root);
    }
}

template <class T>
inline void AVLTree<T>::balanceFromRight(binaryNode<T> *&root)
{
    binaryNode<T> *p;
    binaryNode<T> *w;
    p = root->right;
    switch (p->bfactor)
    {
    case 1: // right high
        root->bfactor = 0;
        p->bfactor = 0;
        rotateToLeft(root);
        break;
    case 0: // even high
        throw std::runtime_error("Right subtree is balanced.");
    case -1: // left high
        w = p->left;
        switch (w->bfactor)
        {
        case -1:
            root->bfactor = 0;
            p->bfactor = 1;
            break;
        case 0:
            root->bfactor = 0;
            p->bfactor = 0;
        case 1:
            root->bfactor = -1;
            p->bfactor = 0;
        }
        w->bfactor = 0;
        rotateToRight(p);
        root->right = p;
        rotateToLeft(root);
    }
}

template <class T>
inline void AVLTree<T>::insertIntoAVL(binaryNode<T> *&root, binaryNode<T> *newNode, bool &isTaller)
{
    if (root == nullptr)
    {
        root = newNode;
        isTaller = true;
    }
    else if (*(root->data) == *(newNode->data))
    {
        throw std::invalid_argument("No duplicates allowed.");
    }
    else if (*(root->data) > *(newNode->data))
    {
        insertIntoAVL(root->left, newNode, isTaller);
        // root->height = 1 + max(this->height(root->left), this->height(root->right));
        if (isTaller)
        {
            switch (root->bfactor)
            {
            case -1:
                balanceFromLeft(root);
                isTaller = false;
                break;
            case 0:
                root->bfactor = -1;
                isTaller = true;
                break;
            case 1:
                root->bfactor = 0;
                isTaller = false;
            }
        }
    }
    else
    {
        insertIntoAVL(root->right, newNode, isTaller);
        // root->height = 1 + max(this->height(root->left), this->height(root->right));
        if (isTaller)
        {
            switch (root->bfactor)
            {
            case -1:
                root->bfactor = 0;
                isTaller = false;
                break;
            case 0:
                root->bfactor = 1;
                isTaller = true;
                break;
            case 1:
                balanceFromRight(root);
                isTaller = false;
            }
        }
    }
}

// Iterator implementation

template <class T>
AVLTree<T>::Iterator::Iterator(binaryNode<T> *root)
{
    pushLeftNodes(root);
}

template <class T>
bool AVLTree<T>::Iterator::hasNext()
{
    return !nodeStack.empty();
}

template <class T>
T AVLTree<T>::Iterator::next()
{
    if (nodeStack.empty())
    {
        throw std::out_of_range("No more elements.");
    }
    binaryNode<T> *node = nodeStack.top();
    nodeStack.pop();
    T data = *(node->data);
    if (node->right != nullptr)
    {
        pushLeftNodes(node->right);
    }
    return data;
}

template <class T>
void AVLTree<T>::Iterator::pushLeftNodes(binaryNode<T> *node)
{
    while (node != nullptr)
    {
        nodeStack.push(node);
        node = node->left;
    }
}

#endif
