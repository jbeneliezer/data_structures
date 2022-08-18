#ifndef AVL_TREE
#define AVL_TREE

#include "BinarySearchTree.h"

enum State { Ok, LeftLeft, RightRight, LeftRight, RightLeft };

template <typename T> class AVLTree : public BinarySearchTree<T> {
private:
  void balance(node<T> *);
  void rotate_left(node<T> *);
  void rotate_right(node<T> *);
  void rotate_left_right(node<T> *);
  void rotate_right_left(node<T> *);

public:
  AVLTree();
  AVLTree(T);
  void insert(T, node<T> *);
};

template <typename T> AVLTree<T>::AVLTree() : BinarySearchTree<T>() {}

template <typename T> AVLTree<T>::AVLTree(T v) : BinarySearchTree<T>(v) {}

template <typename T> void AVLTree<T>::insert(T v, node<T> *n) {
  if (n == nullptr) {
    n = new node<T>(v);
    return;
  }
  if (v > n->value)
    insert(v, n->right);
  else
    insert(v, n->left);
}

#endif
