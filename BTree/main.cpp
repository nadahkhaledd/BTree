#include <iostream>
#include <cmath>
using namespace std;

template<class T, int m>
struct Node
{
    public:
      T keys[m-1];
      Node<T, m> *children[m];
      int mini;
      int keytall;
      bool isLeaf;

      Node(bool);
      void insertb(T);
      void separete(int , Node<T, m> *);
      void print();
};

template<class T, int m>
Node<T, m>::Node( bool isLeaf1)
{
  isLeaf = isLeaf1;
  mini = ceil(m/2.0);
  keytall = 0;
}

template<class T, int m>
void Node<T, m>::insertb(T v)
{
  int check = keytall - 1;

  switch(isLeaf)
  {
      case true :
        while(check >= 0 && keys[check] > v)
        {
          keys[check + 1] = keys[check];
          check--;
        }
        keys[check + 1] = v;
        keytall++;
        break;

      case false:
        while(check >= 0 && keys[check] > v)
          check--;

        if(children[check + 1]->keytall == 2 * mini - 1)
        {
          separete(check + 1, children[check + 1]);
          if (keys[check + 1] < v)
            check++;
        }
        children[check + 1]->insertb(v);
        break;
  }

}

template<class T, int m>
void Node<T, m>::separete(int i, Node<T, m> *n)
{
  Node<T, m> *temp = new Node<T, m>(n->isLeaf);
  temp->keytall = mini - 1;

  int k = 0;
  while(k < mini - 1)
  {
     temp->keys[k] = n->keys[k + mini];
     k++;
  }
  k = 0;

  if(n->isLeaf == false)
  {
      while(k < mini)
      {
          temp->children[k] = n->children[k + mini];
          k++;
      }
  }

  n->keytall = mini - 1;
  for ( k = keytall; k >= i + 1; k--)
    children[k + 1] = children[k];

  children[i + 1] = temp;

  for ( k = keytall - 1; k >= i; k--)
    keys[k + 1] = keys[k];

  keys[i] = n->keys[mini - 1];
  keytall = keytall + 1;
}

template<class T, int m>
void Node<T, m>::print()
{
  int i;
  while(i < keytall)
  {

    if (isLeaf == false)
       children[i]->print();

    cout <<keys[i] << " ";
    i++;
  }

  if (isLeaf == false)
      children[i]->print();
}

template<class T, int m>
class BTree {
  Node<T, m> *highkey;
  int mini;

   public:
  BTree();
  void print();
  void insertb(T v);
};

template<class T, int m>
BTree<T, m>::BTree()
{
    highkey = nullptr;
    mini = ceil(m/2.0);
}

template<class T, int m>
void BTree<T, m>::print()
{
    if (highkey != nullptr)
      highkey->print();
}

template<class T, int m>
void BTree<T, m>::insertb(T v)
{
  if(highkey == nullptr)
  {
    highkey = new Node<T, m>(true);
    highkey->keys[0] = v;
    highkey->keytall = 1;
  }
  else
  {
    if(highkey->keytall == 2 * mini - 1)
    {
      Node<T, m> *temp = new Node<T, m>(false);
      temp->children[0] = highkey;
      temp->separete(0, highkey);

      int i = 0;
      if (temp->keys[0] < v)
        i++;

      temp->children[i]->insertb(v);
      highkey = temp;
    }
    else
      highkey->insertb(v);
  }
}


int main()
{

  BTree<int, 3> t1;
  t1.insertb(1);
  t1.insertb(5);
  t1.insertb(0);
  t1.insertb(4);
  t1.insertb(3);
  t1.insertb(2);

  cout << "\n ";
  t1.print();
  cout << "\n";

  BTree<char, 5> t;
    t.insertb('G');
    t.insertb('I');
    t.insertb('B');
    t.insertb('J');
    t.insertb('C');
    t.insertb('A');
    t.insertb('K');
    t.insertb('E');
    t.insertb('D');
    t.insertb('S');
    t.insertb('T');
    t.insertb('R');
    t.insertb('L');
    t.insertb('F');
    t.insertb('H');
    t.insertb('M');
    t.insertb('N');
    t.insertb('P');
    t.insertb('Q');

  cout << "\n ";
  t.print();
  cout << "\n";
}
