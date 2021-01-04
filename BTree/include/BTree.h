#ifndef BTREE_H
#define BTREE_H
#include <iostream>

using namespace std;

template<class T, int m>
struct Node
{
    private:
       T keys[m-1];
       Node *children[m];
       int keytall;
       int mini;
       bool leaf;

    public:
       Node(bool);
       Node *searchb(T);
       void traverse();
       void insertb(T);
       void split(int, Node);

friend BTree<T,m>;
};

template<class T, int m>
Node::Node(bool l)
{
    leaf = l;
    mini = m/2;
    keytall = 0;

}

template<class T, int m>
void Node::traverse()
{
    for(int i=0; i< keytall; i++)
    {
        if(leaf == false)
        {
            children[i]->traverse();
            cout << " " << keys[i];
        }
        if(leaf == false)
            children[i]->traverse();
    }
}

template<class T, int m>
Node* Node::searchb(T &v)
{
    int i=0;
    while(i<keytall && v>keys[i])
        i++;
    if(keys[i] == v)
        return this;
    if(leaf == true)
        return nullptr;

    return children[i]->searchb(v);
}

template<class T, int m>
void Node::insertb(T &v)
{
    int i = keytall -1;
    if(leaf == true)
    {
        while(i>=0 && keys[i] > v)
        {
            keys[i+1] = keys[i];
            i--;
        }

        keys[i+1] = v;
        keytall+= 1;
    }
    else
    {
        while(i>=0 && keys[i] > v)
            i--;
        if(children[i+1]->keytall == (2* mini - 1))
        {
            split(i+1, children[i+1]);
            if(keys[i+1] < v)
                i++;
        }
        children[i+1]->insertb(v);
    }
}

template<class T, int m>
void Node::split(int i, Node n)
{
    Node *x = new Node(n->leaf);
    x->keytall = mini - 1;

    for(int j=0; j<mini-1; j++)
        x->keys[j] = n->keys[j+mini];

    if(n->leaf == false)
    {
        for(int j=0; j<mini; j++)
            x->children[j] = n->children[j+mini];
    }
    n->keytall = mini -1;
    for(int j=keytall; j>= i+1; j--)
        children[j+1] = children[j];

    children[i+1] = x;
    for(int j= keytall-1; j>=i; j--)
        keys[j+1] = keys[j];
    keys[i] = n->keys[mini-1];
    keytall+=1;
}


template<class T, int m>
class BTree
{
    public:
        BTree();
        void insertb(T&);
        void printb();
        virtual ~BTree();

    protected:

    private:
        Node* root;
        Node* searchb();

};

template<class T, int m>
BTree::BTree()
{
    root = nullptr;
}

template<class T, int m>
void BTree::insertb(T& v)
{
    if(root == nullptr)
    {
        root = new Node(true);
        root->keys[0] = v
        root->keytall = 1;
    }
    else
    {
        if(root->keytall == 2 * mini - 1)
        {
            Node *x = new Node(false);
            x->children[0] = root;
            x->split(0, root);
            int i = 0;
            if(x->keys[0] < v)
                i++;
            x->children[i]->insertb(v);
            root = x;
        }
        else
            root->insertb(v);
    }
}

template<class T, int m>
void BTree::printb()
{
    if(root != nullptr)
        root->traverse();
}

template<class T, int m>
Node* BTree::searchb()
{
    if(root == nullptr)
        return nullptr;
    else
        return root->searchb(v);
}





#endif // BTREE_H
