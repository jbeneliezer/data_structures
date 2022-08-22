#ifndef DOUBLE_LINKED_LIST_H_
#define DOUBLE_LINKED_LIST_H_

#include <iostream>
#include <vector>

using namespace std;

template <typename T> struct DNode {
  T value;
  DNode *next;
  DNode *prev;
  DNode(T v = 0, DNode<T> *n = nullptr, DNode<T> *p = nullptr)
      : value(v), next(n), prev(p) {}
  inline bool operator==(DNode<T> *other) { return (value == other->value); }
};

template <typename T> class DoubleLinkedList {
private:
  DNode<T> *head;
  DNode<T> *tail;

public:
  DoubleLinkedList();
  DoubleLinkedList(T);
  DoubleLinkedList(vector<T>);
  constexpr size_t size();
  T at(DNode<T> *) const;
  void push_back(T);
  void insert(DNode<T> *, T);
  void remove(DNode<T> *);
};

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() : head(new DNode<T>), tail(head) {}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(T v)
    : head(new DNode<T>(v)), tail(head) {}

template <typename T> DoubleLinkedList<T>::DoubleLinkedList(vector<T> vec) {
  for (auto &i : vec) {
    push_back(i);
  }
}

template <typename T> constexpr size_t DoubleLinkedList<T>::size() {
  if (!head)
    return 0;
  size_t sum = 1;
  DNode<T> *n = head;
  while (n != tail) {
    ++sum;
    n = n->next;
  }
  return sum;
}

template <typename T> T DoubleLinkedList<T>::at(DNode<T> *n) const {
  if (!n)
    return 0;
  return n->value;
}

template <typename T> void DoubleLinkedList<T>::push_back(T v) {
  if (!head) {
    head = new DNode<T>(v);
    tail = head;
    return;
  }
  insert(tail, v);
}

template <typename T> void DoubleLinkedList<T>::insert(DNode<T> *n, T v) {
  if (!n) {
    DNode<T> *tmp = new DNode<T>(v, head, nullptr);
    head->prev = tmp;
    head = tmp;
  }
  if (n == tail) {
    n->next = new DNode<T>(v, nullptr, n);
    tail = tail->next;
  } else {
    DNode<T> *tmp = new DNode<T>(v, n->next, n);
    n->next->prev = tmp;
    n->next = tmp;
  }
}

template <typename T> void DoubleLinkedList<T>::remove(DNode<T> *n) {
  if (!n)
    return;
  if (n != head)
    n->prev->next = n->next;
  if (n != tail)
    n->next->prev = n->prev;
  delete n;
}

#endif
