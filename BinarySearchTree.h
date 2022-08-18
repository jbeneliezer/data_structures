#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include "BinaryTree.h"

template <typename T> class BinarySearchTree : public BinaryTree<T> {
public:
  BinarySearchTree();
  BinarySearchTree(T);
  void insert(T, node<T> *);
  node<T> *find(T, node<T> *);
  void remove(node<T> *);
};
template <typename T>
BinarySearchTree<T>::BinarySearchTree() : BinaryTree<T>() {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(T v) : BinaryTree<T>(v) {}

template <typename T> void BinarySearchTree<T>::insert(T v, node<T> *root) {
  if (!root) {
    root = new node<T>(v);
    return;
  }
  if (v > root->value)
    insert(v, root->right);
  else
    insert(v, root->left);
}

template <typename T>
node<T> *BinarySearchTree<T>::find(T needle, node<T> *root) {
  if (!root)
    return nullptr;
  if (root->value == needle)
    return root;
  if (needle > root->value)
    return find(root->right);
  return find(root->left);
}

template <typename T> void BinarySearchTree<T>::remove(node<T> *n) {
  if (!n)
    return;
  node<T> *parent = this.getParent(n, this.getHead());
  node<T> *tmp;
  if (parent)
    if (parent->left == n) {
      parent->left = tmp;
    } else {
      parent->right = tmp;
    }
  if (!n->left && !n->right) {
    // no nothing
  } else if (!n->right) {
    tmp = n->left;
  } else if (!n->left) {
    tmp = n->right;
  } else {
    vector<node<T> *> v;
    this.inOrder(this.getHead(), v);
    for (auto i : v) {
      if (*i == n && i != v.back()) {
        tmp = *i.next();
      } else {
        tmp = *i.prev();
      }
    }
  }
  delete n;
}

#endif
