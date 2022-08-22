#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "BinarySearchTree.h"

template <typename T> class AVLTree : public BinarySearchTree<T> {
private:
  void balance(BNode<T> *);
  void rotate_left(BNode<T> *);
  void rotate_right(BNode<T> *);
  void rotate_left_right(BNode<T> *);
  void rotate_right_left(BNode<T> *);

public:
  AVLTree();
  AVLTree(T);
  void insert(T, BNode<T> *);
  void remove(BNode<T> *);
};

template <typename T> AVLTree<T>::AVLTree() : BinarySearchTree<T>() {}

template <typename T> AVLTree<T>::AVLTree(T v) : BinarySearchTree<T>(v) {}

template <typename T> void AVLTree<T>::balance(BNode<T> *n) {
  if ((height(n->left) - height(n->right)) > 1) {
    if (height(n->left->left) >= height(n->left->right)) {
      rotate_left(n);
    } else {
      rotate_left_right(n);
    }
  } else if ((height(n->right) - height(n->left)) > 1) {
    if (height(n->right->right) >= height(n->right->right)) {
      rotate_right(n);
    } else {
      rotate_right_left(n);
    }
  }
}

template <typename T> void AVLTree<T>::rotate_left(BNode<T> *n) {
  BNode<T> *parent = getParent(n, this->getHead());
  BNode<T> *top = n->right;
  n->right = top->left;
  top->left = n;

  if (parent) {
    if (parent->left == n) {
      parent->left = top;
    } else {
      parent->right = top;
    }
  }
}

template <typename T> void AVLTree<T>::rotate_right(BNode<T> *n) {
  BNode<T> *parent = getParent(n, this->getHead());
  BNode<T> *top = n->left;
  n->left = top->right;
  top->right = n;

  if (parent) {
    if (parent->left == n) {
      parent->left = top;
    } else {
      parent->right = top;
    }
  }
}

template <typename T> void AVLTree<T>::rotate_left_right(BNode<T> *n) {
  rotate_left(n->left);
  rotate_right(n);
}

template <typename T> void AVLTree<T>::rotate_right_left(BNode<T> *n) {
  rotate_right(n->right);
  rotate_left(n);
}

template <typename T> void AVLTree<T>::insert(T v, BNode<T> *root) {
  if (root == nullptr) {
    root = new BNode<T>(v);
    return;
  }
  if (v > root->value)
    insert(v, root->right);
  else
    insert(v, root->left);

  balance(root);
}

template <typename T> void AVLTree<T>::remove(BNode<T> *n) {
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
  while (parent) {
    balance(parent);
    parent = this->getParent(parent, this->getHead());
  }
}

#endif
