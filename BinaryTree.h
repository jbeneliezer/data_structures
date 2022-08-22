#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T> struct BNode {
  T value;
  BNode<T> *left;
  BNode<T> *right;
  BNode(T v = 0, BNode<T> *l = nullptr, BNode<T> *r = nullptr)
      : value(v), left(l), right(r) {}
  inline bool operator==(BNode<T> *other) { return (value == other->value); }
};

template <typename T> class BinaryTree {
private:
  BNode<T> *head;

public:
  BinaryTree();
  BinaryTree(T);
  BNode<T> *getHead();
  // void path(BNode<T> *, BNode<T> *, vector<BNode<T> *> &);
  BNode<T> *getParent(BNode<T> *, BNode<T> *);
  constexpr size_t size(BNode<T> *);
  constexpr size_t height(BNode<T> *);
  T at(BNode<T> *) const;
  BNode<T> *find(T, BNode<T> *);
  void preOrder(BNode<T> *, vector<BNode<T> *> &);
  void inOrder(BNode<T> *, vector<BNode<T> *> &);
  void postOrder(BNode<T> *, vector<BNode<T> *> &);
  void clear(BNode<T> *);
  bool compare(BNode<T> *, BNode<T> *);
};

template <typename T> BinaryTree<T>::BinaryTree() : head(new BNode<T>) {}

template <typename T> BinaryTree<T>::BinaryTree(T v) : head(new BNode<T>(v)) {}

template <typename T> BNode<T> *BinaryTree<T>::getHead() { return head; }

template <typename T>
BNode<T> *BinaryTree<T>::getParent(BNode<T> *n, BNode<T> *root) {
  if (!root)
    return nullptr;
  if (n == root)
    return nullptr;
  if (n == root->left || n == root->right)
    return root;

  BNode<T> *lhs = getParent(n, root->left);
  if (lhs)
    return lhs;
  return getParent(n, root->right);
}

template <typename T> constexpr size_t BinaryTree<T>::size(BNode<T> *root) {
  if (!root)
    return 0;
  return 1 + size(root->left) + size(root->right);
}

template <typename T> constexpr size_t BinaryTree<T>::height(BNode<T> *root) {
  if (!root)
    return 0;
  return 1 + max(height(root->left), height(root->right));
}

template <typename T> T BinaryTree<T>::at(BNode<T> *n) const {
  if (!n)
    return 0;
  return n->value;
}

template <typename T> BNode<T> *BinaryTree<T>::find(T needle, BNode<T> *root) {
  if (!root)
    return nullptr;
  if (root->value == needle)
    return root;
  BNode<T> *ret = find(needle, root->left);
  if (ret)
    return ret;
  return find(needle, root->right);
}

template <typename T>
void BinaryTree<T>::preOrder(BNode<T> *root, vector<BNode<T> *> &v) {
  if (!root)
    return;
  v.push_back(root->value);
  preOrder(root->left, v);
  preOrder(root->right, v);
}

template <typename T>
void BinaryTree<T>::inOrder(BNode<T> *root, vector<BNode<T> *> &v) {
  if (!root)
    return;
  inOrder(root->left, v);
  v.push_back(root);
  inOrder(root->right, v);
}

template <typename T>
void BinaryTree<T>::postOrder(BNode<T> *root, vector<BNode<T> *> &v) {
  if (!root)
    return;
  postOrder(root->left, v);
  postOrder(root->right, v);
  v.push_back(root->value);
}

template <typename T> void BinaryTree<T>::clear(BNode<T> *root) {
  if (!root)
    return;
  clear(root->left);
  clear(root->right);
  delete (root);
}

template <typename T>
bool BinaryTree<T>::compare(BNode<T> *root, BNode<T> *other) {
  if (!root && !other)
    return true;
  if ((!root && other) || (root && other))
    return false;
  if (root->value != other->value)
    return false;
  return compare(root->left, other->left) && compare(root->right, other->right);
}

#endif
