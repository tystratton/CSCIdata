#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"
#include <stdexcept>

template <class t>
class binarySearchTree : public binaryTree<t>
{
public:
  void insert(const t &insertItem);
  bool search(const t &searchItem);
  void deleteNode(const t &deleteItem);
  std::string printItem(const t &searchItem) const;

private:
  void deleteFromTree(binaryNode<t> *&p);
  bool search(const t &searchItem, binaryNode<t> *p);
  void insert(binaryNode<t> *&insertItem, binaryNode<t> *&p);
  std::ostringstream printItem(const t &searchItem, binaryNode<t> *p) const;
};

template <class t>
void binarySearchTree<t>::insert(const t &insertItem)
{
  binaryNode<t> *newNode;
  newNode = new binaryNode<t>;
  newNode->data = new t(insertItem);
  newNode->left = nullptr;
  newNode->right = nullptr;
  insert(newNode, this->getRoot());
}

template <class t>
bool binarySearchTree<t>::search(const t &searchItem)
{
  return search(searchItem, this->getRoot());
}

template <class t>
void binarySearchTree<t>::deleteNode(const t &deleteItem)
{
  binaryNode<t> *current;
  binaryNode<t> *trailCurrent;
  bool found = false;
  if (this->getRoot() == nullptr)
    throw std::invalid_argument("Cannot delete from an empty tree");
  else
    current = this->getRoot();
  trailCurrent = current;
  while (current != nullptr && !found)
  {
    if (*(current->data) == deleteItem)
      found = true;
    else
    {
      trailCurrent = current;
      if (*(current->data) > deleteItem)
      {
        current = current->left;
      }
      else
        current = current->right;
    }
  }
  if (current == nullptr || !found)
    throw std::invalid_argument("The item to be deleted is not in the tree.");
  else if (found)
  {
    if (current == this->getRoot())
      deleteFromTree(this->getRoot());
    else if (*trailCurrent->data > deleteItem)
      deleteFromTree(trailCurrent->left);
    else
      deleteFromTree(trailCurrent->right);
  }
}

template <class t>
inline std::string binarySearchTree<t>::printItem(const t &searchItem) const
{
  if (search(searchItem))
    return printItem(searchItem, this->getRoot()).str();

  return "The item does not exist in the tree.";
}

template <class t>
void binarySearchTree<t>::deleteFromTree(binaryNode<t> *&p)
{
  binaryNode<t> *current;
  binaryNode<t> *trailCurrent;
  binaryNode<t> *temp;
  if (p == nullptr)
    throw std::invalid_argument("The item to be deleted is not in the tree.");
  else if (p->left == nullptr && p->right == nullptr)
  {
    temp = p;
    p = nullptr;
    delete temp;
  }
  else if (p->left == nullptr)
  {
    temp = p;
    p = temp->right;
    delete temp;
  }
  else if (p->right == nullptr)
  {
    temp = p;
    p = temp->left;
    delete temp;
  }
  else
  {
    current = p->left;
    trailCurrent = nullptr;
    while (current->right != nullptr)
    {
      trailCurrent = current;
      current = current->right;
    }
    t *tempData;
    tempData = p->data;
    p->data = current->data;
    current->data = tempData;
    if (trailCurrent == nullptr)
      p->left = current->left;
    else
      trailCurrent->right = current->left;

    delete current;
  }
}

template <class t>
bool binarySearchTree<t>::search(const t &searchItem, binaryNode<t> *p)
{
  if (p == nullptr)
  {
    return false;
  }
  else if (*(p->data) == searchItem)
    return true;
  else if (*(p->data) > searchItem)
    return search(searchItem, p->left);
  else
    return search(searchItem, p->right);
}

template <class t>
void binarySearchTree<t>::insert(binaryNode<t> *&insertItem, binaryNode<t> *&p)
{
  if (p == nullptr)
  {
    p = insertItem;
  }
  else if (*(p->data) == *(insertItem->data))
  {
    throw std::invalid_argument("The item to be inserted is already in the tree -- duplicates are not allowed.");
  }
  else if (*(p->data) > *(insertItem->data))
  {
    insert(insertItem, p->left);
  }
  else
  {
    insert(insertItem, p->right);
  }
}
template <class t>
inline std::ostringstream binarySearchTree<t>::printItem(const t &searchItem, binaryNode<t> *p) const
{
  std::ostringstream out;
  if (p == nullptr)
  {
    out << "The item does not exist in the tree.";
  }
  else if (*(p->data) == searchItem)
    out << *p->data << std::endl;
  else if (*(p->data) > searchItem)
    return printItem(searchItem, p->lTree);
  else
    return printItem(searchItem, p->rTree);

  return out;
}
#endif