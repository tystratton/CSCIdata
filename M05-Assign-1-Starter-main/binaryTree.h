#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <sstream>

using namespace std;

template <class elemType>
struct nodeType
{
  elemType *info;
  nodeType<elemType> *lLink;
  nodeType<elemType> *rLink;
  ~nodeType() { delete info; }
};

template <class elemType>
class binaryTreeType
{
public:
  const binaryTreeType<elemType> &operator=(const binaryTreeType<elemType> &otherTree);
  bool isEmpty() const;
  void inorderTraversal() const;
  std::string preorderTraversal() const;
  void postorderTraversal() const;
  int treeHeight() const;
  int treeNodeCount(const elemType &searchItem) const;
  int treeLeavesCount(const elemType &searchItem) const;
  void destroyTree();
  virtual bool search(const elemType &searchItem) const = 0;
  virtual void insert(const elemType &insertItem) = 0;
  virtual void deleteNode(const elemType &deleteItem) = 0;
  binaryTreeType(const binaryTreeType<elemType> &otherTree);
  binaryTreeType();
  ~binaryTreeType();

protected:
  nodeType<elemType> *root;

private:
  void copyTree(nodeType<elemType> *&copiedTreeRoot, nodeType<elemType> *otherTreeRoot);
  void destroy(nodeType<elemType> *&p);
  void inorder(nodeType<elemType> *p) const;
  void preorder(nodeType<elemType> *p, std::ostringstream &) const;
  void postorder(nodeType<elemType> *p) const;
  int height(nodeType<elemType> *p) const;
  int max(int x, int y) const;
  int nodeCount(const elemType &searchItem, nodeType<elemType> *p, int count = 0) const;
  int leavesCount(const elemType &searchItem, nodeType<elemType> *p, int count = 0) const;
};

template <class elemType>
bool binaryTreeType<elemType>::isEmpty() const
{
  return (root == nullptr);
}

template <class elemType>
binaryTreeType<elemType>::binaryTreeType()
{
  root = nullptr;
}

template <class elemType>
void binaryTreeType<elemType>::inorderTraversal() const
{
  inorder(root);
}

template <class elemType>
std::string binaryTreeType<elemType>::preorderTraversal() const
{
  std::ostringstream out;
  preorder(root, out);
  return out.str();
}

template <class elemType>
void binaryTreeType<elemType>::postorderTraversal() const
{
  postorder(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeHeight() const
{
  return height(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeNodeCount(const elemType &searchItem) const
{
  return nodeCount(searchItem, root);
}

template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount(const elemType &searchItem) const
{
  return leavesCount(searchItem, root);
}

template <class elemType>
void binaryTreeType<elemType>::destroy(nodeType<elemType> *&p)
{
  if (p != nullptr)
  {
    destroy(p->lLink);
    destroy(p->rLink);
    delete p;
    p = nullptr;
  }
}

template <class elemType>
void binaryTreeType<elemType>::destroyTree()
{
  destroy(root);
}

template <class elemType>
binaryTreeType<elemType>::~binaryTreeType()
{
  destroy(root);
}

template <class elemType>
void binaryTreeType<elemType>::inorder(nodeType<elemType> *p) const
{
  /*1. inorder left sub tree
  2. visit the current node
  3. inorder right sub tree */
  if (p != nullptr)
  {
    inorder(p->lLink);
    cout << *p->info << "\n\n";
    inorder(p->rLink);
  }
}

template <class elemType>
void binaryTreeType<elemType>::preorder(nodeType<elemType> *p, std::ostringstream &out) const
{
  /*1. visit current node
  2. preorder left sub tree
  3. preorder right sub tree*/
  if (p != nullptr)
  {
    out << *p->info << "\n\n";
    preorder(p->lLink, out);
    preorder(p->rLink, out);
  }
}

template <class elemType>
void binaryTreeType<elemType>::postorder(nodeType<elemType> *p) const
{
  /*1. preorder right sub tree
  2. preorder left sub tree
  3. visit current node*/
  if (p != nullptr)
  {
    postorder(p->lLink);
    postorder(p->rLink);
    cout << *p->info << "\n\n";
  }
}

template <class elemType>
int binaryTreeType<elemType>::height(nodeType<elemType> *p) const
{
  if (p == nullptr)
    return 0;
  else
    return 1 + max(height(p->lLink), height(p->rLink));
}

template <class elemType>
int binaryTreeType<elemType>::max(int x, int y) const
{
  if (x >= y)
    return x;
  else
    return y;
}

template <class elemType>
binaryTreeType<elemType>::binaryTreeType(const binaryTreeType<elemType> &otherTree)
{
  if (otherTree == nullptr)
    root = nullptr;
  else
    copyTree(root, otherTree.root);
}

template <class elemType>
const binaryTreeType<elemType> &binaryTreeType<elemType>::operator=(const binaryTreeType<elemType> &otherTree)
{
  if (this != &otherTree)
  {
    if (root != nullptr)
      destroy(root);
    if (otherTree.root == nullptr)
      root = nullptr;
    else
      copyTree(root, otherTree.root);
  }
  return *this;
}

template <class elemType>
void binaryTreeType<elemType>::copyTree(nodeType<elemType> *&copiedTreeRoot, nodeType<elemType> *otherTreeRoot)
{
  if (otherTreeRoot == nullptr)
    copiedTreeRoot = nullptr;
  else
  {
    copiedTreeRoot = new nodeType<elemType>;
    copiedTreeRoot->info = otherTreeRoot->info;
    copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink);
    copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
  }
}

// lab=> implement both of these
template <class elemType>
int binaryTreeType<elemType>::nodeCount(const elemType &searchItem, nodeType<elemType> *p, int count) const
{

  if (p == nullptr)
    return count;
  else if (*p->info == searchItem)
    return count + 1;
  else if (*p->info > searchItem)
    return nodeCount(searchItem, p->lLink, count + 1);
  else
    return nodeCount(searchItem, p->rLink, count + 1);
}

template <class elemType>
int binaryTreeType<elemType>::leavesCount(const elemType &searchItem, nodeType<elemType> *p, int count) const
{
  // int count = 0;
  if (p == nullptr)
    return count;
  if ((p->lLink == nullptr) && (p->rLink == nullptr))
    count += 1;
  if (*p->info == searchItem)
    return count;
  if (p->lLink != nullptr && *p->info > searchItem)
    count = leavesCount(searchItem, p->lLink, count);
  if (p->rLink != nullptr && searchItem > *p->info)
    count = leavesCount(searchItem, p->rLink, count);
  return count;
}

#endif