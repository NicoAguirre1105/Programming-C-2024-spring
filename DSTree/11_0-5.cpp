#include <iostream>
#include <cstdlib>
#include <string>

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
    string data;
    Node *one;
    Node *zero;
    Node(int k, string d, Node *o=nullptr, Node *z=nullptr): key(k), data(d), one(o), zero(z) {}
    Node(): data(""), key(NULL), one(nullptr), zero(nullptr) {}
};

void f_print(Node* r, int indent = 1) 
{
    if (r == nullptr) return;
    f_print(r->zero, indent + 3);
    for (int i = 0; i < indent; ++i)
        cout << ' ';
    cout << "(" << r->key << ", " << r->data << ")" << endl;
    f_print(r->one, indent + 3);
}

class DSTree
{
    public:
    Node *root=nullptr;
    DSTree(Node *r): root(r) {}
    DSTree () {
        int key;
        string data;

        while(cout << "Type key: ", cin >> key, key != -1)
        {
            cout << "Type data (string): "; cin >> data;
            Node *new_n = new Node(key, data);
            this->insert(new_n);
        }
        cout << endl;
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
        cout << "ERROR: Keys can't be repeated" << endl;
        exit(-1);
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
    Node *p6 = new Node(3, "011"),
    *p9 = new Node(7, "111", nullptr, p6),
    // *p8 = new Node(-2, "-2"),
    *p7 = new Node(5, "101", p9),
    *p1 = new Node (4, "100"),
    *p5 = new Node(2, "10", nullptr, p1),
    *p2 = new Node(1, "1", p7, p5);

    DSTree G;
    G.print();
    cout << digit(5, 1) << endl;
    cout << G.find(3)->data << endl;
    cout << G.root->zero->key << endl;


    return EXIT_SUCCESS;
}