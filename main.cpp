#include "BinarySearchTree.h"
#include "BinaryTree.h"
#include "DoubleLinkedList.h"
#include "LinkedList.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  vector<int> test(4, 20);
  LinkedList<int> l(test);
  DoubleLinkedList<int> dl(test);
  BinaryTree<int> bt(0);
  BinarySearchTree<int> bst(0);

  return 0;
}
