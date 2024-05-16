#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int digit(int x, int n)
{
    return (x >> n) & 1;
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
    DSTree (DSTree &T)
    {
        root = n_copy(T.copy());
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

    void add(DSTree *T)
    {
        n_add(this, T->root);
    }

    void del(int key)
    {
        Node *aux = root;
        int depth = 0;

        while(aux != nullptr && aux->key != key)
        {
            if(digit(key, depth))
                aux = aux->one;
            else
                aux = aux->zero;
            depth++;
        }

        if(aux == nullptr)
        {
            cout << "Key not found" << endl;
            return;
        }

        if(aux->one == nullptr && aux->zero == nullptr)
        {
            delete aux;
            aux = nullptr;
        } else 
        {
            Node *change = aux;
            while(change->one != nullptr && change->zero != nullptr)
            {
                if(change->one != nullptr)
                    change = change->one;
                else
                    change = change->zero;
            }
            aux = change;
            change = nullptr;
        }
    }

    Node* copy()
    {
        return n_copy(root);
    }

    void mask1(int mask)
    {
        n_mask1(root, mask);
    }

    void mask2(int key, int mask)
    {
        n_mask2(root, key, mask);
    }

    bool check()
    {
        return n_check(root, 0);
    }

    static void n_des(Node *&p);
    static void n_insert(Node *p, Node *new_node, int pos);
    static Node* n_copy(Node *p);
    static void n_add(DSTree *G, Node *p);
    static void n_mask1(Node *p, int mask);
    static void n_mask2(Node *p,int key, int mask);
    static bool n_check(Node *p, int depth);
};

void DSTree::n_mask2(Node *p,int key, int mask)
{
    if(p == nullptr)
        return;

    if((mask & ~(key ^ p->key)) == mask)
    {
        cout << p->key << endl;
    }
    n_mask2(p->one, key, mask);
    n_mask2(p->zero, key, mask);
}

void DSTree::n_mask1(Node *p, int mask)
{
    if(p == nullptr)
        return;

    if((p->key & mask) == mask)
    {
        cout << p->key << endl;
    }
    n_mask1(p->one, mask);
    n_mask1(p->zero, mask);
}

void DSTree::n_add(DSTree *G, Node *p)
{
    if(p == nullptr)
        return;
    G->insert(p);
    n_add(G, p->one);
    n_add(G, p->zero);
}

Node *DSTree::n_copy(Node *p)
{
    if (p == nullptr)
        return nullptr;

    Node *q = new Node(p->key, p->data, n_copy(p->one), n_copy(p->zero));
    return q;
}

void DSTree::n_des(Node *&n)
{
    if (n == nullptr)
        return;
    n_des(n->one);
    n_des(n->zero);
    delete n;
}

bool DSTree::n_check(Node *p, int depth)
{
    if(p == nullptr)
        return true;

    if(p->one != nullptr)
        if(!digit(p->one->key, depth))
            return false; 

    if(p->zero != nullptr)
        if(digit(p->zero->key, depth))
            return false;

    return (n_check(p->one, depth+1) && n_check(p->zero, depth + 1));
}       

void DSTree::n_insert(Node *p, Node *new_node, int pos)
{
    if(p->key == new_node->key)
    {
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
    DSTree G1;
    DSTree G2;
    DSTree G = G1;
    G.del(5);
    G.print();
    G1.print();

    int x = (5 & (~(9 ^ 5)));

    cout << x << endl; 

    return EXIT_SUCCESS;
}