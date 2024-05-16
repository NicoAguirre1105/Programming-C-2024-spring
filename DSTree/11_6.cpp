#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

int digit(int x, int n)
{
    return (x >> n) % 2;
}

// template <class T>
struct Node
{
    int key;
    // T data;
    int data;
    Node *one;
    Node *zero;
    Node(int k, int d=1, Node *o=nullptr, Node *z=nullptr): key(k), data(d), one(o), zero(z) {}
    Node(): data(1), key(NULL), one(nullptr), zero(nullptr) {}
};

void f_print(Node* r) 
{
    if (r == nullptr) return;
    cout << r->key << " " << r->data << endl;
    f_print(r->zero);
    f_print(r->one);
}

class DSTree
{
    public:
    Node *root=nullptr;
    DSTree(Node *r): root(r) {}
    DSTree () {
        ifstream fin("text.in");
        int key;

        while(fin >> key, key != -1)
        {
            Node *new_n = new Node(key);
            this->insert(new_n);
        }
    }

    ~DSTree()
    {
        n_des(root);
        root = nullptr;
    }

    void print()
    {
        f_print(root);
    }

    Node *find(int key)
    {
        Node *aux = root;
        int pos = 0;
        while (aux != nullptr)
        {
            if(key == aux->key)
                return aux;
            if(digit(key, pos))
                aux = aux->one;
            else
                aux = aux->zero;
            pos++;
        }
        return aux;
    }

    void insert(Node *p)
    {
        if(root == nullptr)
            root = p;
        else
            n_insert(root, p, 0);
    }

    void del(int key)
    {
        n_del(root, key, 0);
    }

    static void n_des(Node *&p);
    static void n_insert(Node *p, Node *new_node, int pos);
    static void n_del(Node *&p, int key, int depth);
};

void DSTree::n_del(Node *&p, int key, int depth)
{
    if (p->key == key)
    {
        delete p;
        p = nullptr;
        return;
    }

    if(digit(key, depth))
    {
        if(p->one != nullptr)
            n_del(p->one, key, depth + 1);
        else
            cout << "Key not found" << endl;
    } else 
    {
        if(p->zero != nullptr)
            n_del(p->zero, key, depth + 1);
        else
            cout << "Key not found" << endl;
    }
}

void DSTree::n_des(Node *&n)
{
    if (n == nullptr)
        return;
    n_des(n->one);
    n_des(n->zero);
    delete n;
}

void DSTree::n_insert(Node *p, Node *new_node, int pos)
{
    if(p->key == new_node->key)
    {
        p->data++;
        return;
    }

    if(digit(new_node->key, pos))
    {
        if(p->one == nullptr)
            p->one = new_node;
        else
            n_insert(p->one, new_node, pos + 1);
    } else 
    {
        if(p->zero == nullptr)
            p->zero = new_node;
        else
            n_insert(p->zero, new_node, pos + 1);
    }
}

int main()
{ 
    DSTree G;
    G.print();

    return EXIT_SUCCESS;
}