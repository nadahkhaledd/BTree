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
  int i = keytall - 1;

  if (isLeaf == true)
  {
    while (i >= 0 && keys[i] > v)
    {
      keys[i + 1] = keys[i];
      i--;
    }
    keys[i + 1] = v;
    keytall = keytall + 1;
  }

   else
   {
    while (i >= 0 && keys[i] > v)
      i--;

    if (children[i + 1]->keytall == 2 * mini - 1)
    {
      separete(i + 1, children[i + 1]);
      if (keys[i + 1] < v)
        i++;
    }
    children[i + 1]->insertb(v);
  }
}

template<class T, int m>
void Node<T, m>::separete(int i, Node<T, m> *n)
{
  Node<T, m> *temp = new Node<T, m>(n->isLeaf);
  temp->keytall = mini - 1;

  for (int j = 0; j < mini - 1; j++)
    temp->keys[j] = n->keys[j + mini];

  if (n->isLeaf == false)
  {
    for (int j = 0; j < mini; j++)
    temp->children[j] = n->children[j + mini];
  }

  n->keytall = mini - 1;
  for (int j = keytall; j >= i + 1; j--)
    children[j + 1] = children[j];

  children[i + 1] = temp;

  for (int j = keytall - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = n->keys[mini - 1];
  keytall = keytall + 1;
}

template<class T, int m>
void Node<T, m>::print()
{
  int i;
  for (i = 0; i < keytall; i++)
  {

    if (isLeaf == false)
    {
        cout << "\n";
       children[i]->print();
    }
    cout <<keys[i] << ", ";
  }

  if (isLeaf == false)
  {
      cout << "\n";
      children[i]->print();
  }

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
    highkey = NULL;
    mini = ceil(m/2.0);
    cout << mini << endl;
}

template<class T, int m>
void BTree<T, m>::print()
{
    if (highkey != NULL)
      highkey->print();
}

template<class T, int m>
void BTree<T, m>::insertb(T v)
{
  if (highkey == NULL)
  {
    highkey = new Node<T, m>(true);
    highkey->keys[0] = v;
    highkey->keytall = 1;
  }
  else
  {
    if (highkey->keytall == 2 * mini - 1)
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

    /*BTree<int, 5> t;
    t.insertb(10);
    t.insertb(20);
    t.insertb(5);
    t.insertb(6);
    t.insertb(12);
    t.insertb(30);
    t.insertb(7);
    t.insertb(17);*/

  BTree<int, 3> t;
  t.insertb(1);
  t.insertb(5);
  t.insertb(0);
  t.insertb(4);
  t.insertb(3);
  t.insertb(2);

  /*BTree<char, 5> t;
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
    t.insertb('Q');*/

  cout << "\nThe B-tree is\n ";
  t.print();
  cout << "\n";
}
