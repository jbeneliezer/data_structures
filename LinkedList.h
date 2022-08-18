#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>
#include <vector>

using namespace std;

template <typename T> struct Node {
  T value;
  Node *next;
  Node(T v = 0, Node<T> *n = nullptr) : value(v), next(n) {}
};

template <typename T> class LinkedList {
private:
  Node<T> *head;

public:
  LinkedList();
  LinkedList(T);
  LinkedList(vector<T>);
  constexpr size_t size();
  T at(Node<T> *) const;
  T atIndex(int) const;
  void push_back(T);
  void insert(Node<T> *, T);
  void remove(Node<T> *);
};

template <typename T> LinkedList<T>::LinkedList() : head(new Node<T>) {}

template <typename T> LinkedList<T>::LinkedList(T v) : head(new Node<T>(v)) {}

template <typename T> LinkedList<T>::LinkedList(vector<T> vec) {
  for (auto &i : vec) {
    push_back(i);
  }
}

template <typename T> constexpr size_t LinkedList<T>::size() {
  size_t sum = 0;
  Node<T> *n = head;
  while (n) {
    ++sum;
    n = n->next;
  }
  return sum;
}

template <typename T> T LinkedList<T>::at(Node<T> *n) const {
  if (!n)
    return 0;
  return n->value;
}

template <typename T> T LinkedList<T>::atIndex(int n) const {
  Node<T> *walk = head;
  while (n-- > 0 && walk) {
    walk = walk->next;
  }
  return walk->value;
}

template <typename T> void LinkedList<T>::push_back(T v) {
  if (!head) {
    head = new Node<T>(v);
    return;
  }
  Node<T> *n = head;
  while (n->next) {
    n = n->next;
  }
  insert(n, v);
}

template <typename T> void LinkedList<T>::insert(Node<T> *n, T v) {
  if (!n) {
    Node<T> *tmp = new Node<T>(v, head);
    head = tmp;
  }
  n->next = new Node<T>(v, n->next);
}

template <typename T> void LinkedList<T>::remove(Node<T> *n) {
  if (!head)
    return;
  Node<T> walk = head;
  while (walk->next != n && walk->next) {
    walk = walk->next;
  }

  if (!walk->next)
    return;

  if (!walk->next->next) {
    delete walk->next;
  } else {
    Node<T> *tmp = walk->next;
    walk->next = walk->next->next;
    delete tmp;
  }
}

#endif
