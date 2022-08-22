#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include "BinaryTree.h"

#include <iterator>
#include <vector>

using namespace std;

template <typename T> class BinarySearchTree : public BinaryTree<T> {
public:
  BinarySearchTree();
  BinarySearchTree(T);
  void insert(T, BNode<T> *);
  BNode<T> *find(T, BNode<T> *);
  void remove(BNode<T> *);
};
template <typename T>
BinarySearchTree<T>::BinarySearchTree() : BinaryTree<T>() {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(T v) : BinaryTree<T>(v) {}

template <typename T> void BinarySearchTree<T>::insert(T v, BNode<T> *root) {
  if (!root) {
    root = new BNode<T>(v);
    return;
  }
  if (v > root->value)
    insert(v, root->right);
  else
    insert(v, root->left);
}

template <typename T>
BNode<T> *BinarySearchTree<T>::find(T needle, BNode<T> *root) {
  if (!root)
    return nullptr;
  if (root->value == needle)
    return root;
  if (needle > root->value)
    return find(root->right);
  return find(root->left);
}

template <typename T> void BinarySearchTree<T>::remove(BNode<T> *n) {
  if (!n)
    return;
  BNode<T> *parent = this->getParent(n, this->getHead());
  BNode<T> *tmp;

  if (!n->left && !n->right) {
    // no nothing
  } else if (!n->right) {
    tmp = n->left;
  } else if (!n->left) {
    tmp = n->right;
  } else {
    vector<BNode<T> *> v;
    this->inOrder(this->getHead(), v);
    for (auto i = v.begin(); i != v.end(); ++i) {
      if (*i == n) {
        if (*i != v.back()) {
          tmp = *(++i);
          break;
        } else {
          tmp = *(--i);
          break;
        }
      }
    }
  }

  if (parent) {
    if (parent->left == n) {
      parent->left = tmp;
    } else {
      parent->right = tmp;
    }
  }

  delete n;
}

#endif
