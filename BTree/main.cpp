#include <iostream>
#include <cmath>
using namespace std;

template<class T>
class Node {
public:
  T *keys;
  int t;
  Node<T> **C;
  int n;
  bool leaf;
  Node(int _t, bool _leaf);
  void insertNonFull(T k);
  void splitChild(int i, Node<T> *y);
  void traverse();

};

template<class T>
class BTree {
  Node<T> *root;
  int t;

   public:
  BTree(int _t) {
    root = NULL;
    t = _t;
  }

  void traverse() {
    if (root != NULL)
      root->traverse();
  }

  void insert(T k);
};

template<class T>
Node<T>::Node(int t1, bool leaf1) {
  t = t1;
  leaf = leaf1;

  keys = new T[2 * t - 1];
  C = new Node *[2 * t];

  n = 0;
}

template<class T>
void Node<T>::traverse() {
  int i;
  for (i = 0; i < n; i++) {
      cout << " " << keys[i];
    if (leaf == false)
      C[i]->traverse();
  }

  if (leaf == false)
    C[i]->traverse();
}

template<class T>
void BTree<T>::insert(T k) {
  if (root == NULL) {
    root = new Node<T>(t, true);
    root->keys[0] = k;
    root->n = 1;
  } else {
    if (root->n == 2 * t - 1) {
      Node<T> *s = new Node<T>(t, false);

      s->C[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->C[i]->insertNonFull(k);

      root = s;
    } else
      root->insertNonFull(k);
  }
}

template<class T>
void Node<T>::insertNonFull(T k) {
  int i = n - 1;

  if (leaf == true) {
    while (i >= 0 && keys[i] > k) {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = k;
    n = n + 1;
  } else {
    while (i >= 0 && keys[i] > k)
      i--;

    if (C[i + 1]->n == 2 * t - 1) {
      splitChild(i + 1, C[i + 1]);

      if (keys[i + 1] < k)
        i++;
    }
    C[i + 1]->insertNonFull(k);
  }
}

template<class T>
void Node<T>::splitChild(int i, Node<T> *y) {
  Node<T> *z = new Node<T>(y->t, y->leaf);
  z->n = t - 1;

  for (int j = 0; j < t - 1; j++)
    z->keys[j] = y->keys[j + t];

  if (y->leaf == false) {
    for (int j = 0; j < t; j++)
      z->C[j] = y->C[j + t];
  }

  y->n = t - 1;
  for (int j = n; j >= i + 1; j--)
    C[j + 1] = C[j];

  C[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[t - 1];
  n = n + 1;
}

int main() {

    BTree<int> t(3);
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

  /*BTree<int> t1(2);
  t1.insert(1);
  t1.insert(5);
  t1.insert(0);
  t1.insert(4);
  t1.insert(3);
  t1.insert(2);*/

  /*BTree<char> t(3);
    t.insert('G');
    t.insert('I');
    t.insert('B');
    t.insert('J');
    t.insert('C');
    t.insert('A');
    t.insert('K');
    t.insert('E');
    t.insert('D');
    t.insert('S');
    t.insert('T');
    t.insert('R');
    t.insert('L');
    t.insert('F');
    t.insert('H');
    t.insert('M');
    t.insert('N');
    t.insert('P');
    t.insert('Q');*/

  cout << "\nThe B-tree is: ";
  t.traverse();
  cout << "\n";
}
