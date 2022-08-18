#ifndef BINARY_TREE
#define BINARY_TREE

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
};

template <typename T> using node = struct BNode<T>;

template <typename T> class BinaryTree {
private:
  node<T> *head;

public:
  BinaryTree();
  BinaryTree(T);
  node<T> *getHead();
  node<T> *getParent(node<T> *, node<T> *);
  constexpr size_t size(node<T> *);
  constexpr size_t height(node<T> *);
  T at(node<T> *) const;
  node<T> *find(T, node<T> *);
  void preOrder(node<T> *, vector<T> &);
  void inOrder(node<T> *, vector<T> &);
  void postOrder(node<T> *, vector<T> &);
  virtual void remove(node<T> *);
  void clear(node<T> *);
  bool compare(node<T> *, node<T> *);
};

template <typename T> BinaryTree<T>::BinaryTree() : head(new node<T>) {}

template <typename T> BinaryTree<T>::BinaryTree(T v) : head(new node<T>(v)) {}

template <typename T> node<T> *BinaryTree<T>::getHead() { return head; }

template <typename T>
node<T> *BinaryTree<T>::getParent(node<T> *n, node<T> *root) {
  if (!root)
    return nullptr;
  if (n == root)
    return nullptr;
  if (n == root->left || n == root->right)
    return root;
  return getParent(n, root->left) || getParent(n, root->right);
}

template <typename T> constexpr size_t BinaryTree<T>::size(node<T> *root) {
  if (!root)
    return 0;
  return 1 + size(root->left) + size(root->right);
}

template <typename T> constexpr size_t BinaryTree<T>::height(node<T> *root) {
  if (!root)
    return 0;
  return 1 + max(height(root->left), height(root->right));
}

template <typename T> T BinaryTree<T>::at(node<T> *n) const {
  if (!n)
    return 0;
  return n->value;
}

template <typename T> node<T> *BinaryTree<T>::find(T needle, node<T> *root) {
  if (!root)
    return nullptr;
  if (root->value == needle)
    return root;
  node<T> *ret = find(needle, root->left);
  if (ret)
    return ret;
  return find(needle, root->right);
}

template <typename T>
void BinaryTree<T>::preOrder(node<T> *root, vector<T> &v) {
  if (!root)
    return;
  v.push_back(root->value);
  preOrder(root->left, v);
  preOrder(root->right, v);
}

template <typename T> void BinaryTree<T>::inOrder(node<T> *root, vector<T> &v) {
  if (!root)
    return;
  inOrder(root->left, v);
  v.push_back(root->value);
  inOrder(root->right, v);
}

template <typename T>
void BinaryTree<T>::postOrder(node<T> *root, vector<T> &v) {
  if (!root)
    return;
  postOrder(root->left, v);
  postOrder(root->right, v);
  v.push_back(root->value);
}

template <typename T> void BinaryTree<T>::clear(node<T> *root) {
  if (!root)
    return;
  clear(root->left);
  clear(root->right);
  delete (root);
}

template <typename T>
bool BinaryTree<T>::compare(node<T> *root, node<T> *other) {
  if (!root && !other)
    return true;
  if ((!root && other) || (root && other))
    return false;
  if (root->value != other->value)
    return false;
  return compare(root->left, other->left) && compare(root->right, other->right);
}

#endif
