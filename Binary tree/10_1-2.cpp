#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

struct Node
{
    int key;
    string data;
    Node *right;
    Node *left;
    Node(int k, string d, Node *r=nullptr, Node *l=nullptr): data(d), right(r), left(l), key(k) {}
};

void f_print(Node* r, int indent = 1) 
{
    if (r == nullptr) return;
    f_print(r->right, indent + 3);
    for (int i = 0; i < indent; ++i)
        cout << ' ';
    cout << r->key << endl;
    f_print(r->left, indent + 3);
}


class Tree
{
    Node *root=nullptr;

    public:
    Tree(Node *r): root(r) {}
    Tree() 
    {
        int key;
        string data; 

        while(cout << "Type key: ", cin >> key, key != -1)
        {
            cout << "Type data (string): "; cin >> data;
            Node *new_n = new Node(key, data);
            this->insert_rec(new_n);
        }
    }

    void insert_rec(Node *p)
    {
        if(root == nullptr)
        {
            root = p;
            return;
        }
        n_insert(root, p);
    }

    void insert_cycle(Node *p)
    {
        if(root == nullptr)
        {
            root = p;
            return;
        }
        Node *aux = root;
        while(aux != nullptr)
        {
            if (p->key == aux->key)
            {
                cout << "ERROR: Keys can not be repeated.";
                exit(-1);
            }

            if (p->key < aux->key)
            {
                if (aux->left == nullptr)
                {
                    aux->left = p;
                    return;
                } else
                    aux = aux->left;
            }
            else
            {
                if (aux->right == nullptr)
                {
                    aux->right = p;
                    return;
                } else
                    aux = aux->right;
            }
        }
    }

    Node *find_cycle(int key)
    {
        Node *aux = root;

        while (aux != nullptr)
        {
            if (aux->key == key)
                return aux;
            else if (key < aux->key)
                aux = aux->left;
            else
                aux = aux->right;
        }
        return aux;
    }

    void print()
    {
        f_print(root);
        cout << "----------------" << endl;
    }

    private:
    static int n_count(Node *p);
    static void n_insert(Node *p, Node *new_n);
    static Node *n_find(Node *p, int key);
};

int Tree::n_count(Node *p)
{
    if (p == nullptr)
        return 0;
    
    return 1 + n_count(p->left) + n_count(p->right);
}

void Tree::n_insert(Node *p, Node *new_n)
{
    if (new_n->key == p->key)
    {
        cout << "ERROR: Keys can not be repeated.";
        exit(-1);
    }

    if (new_n->key < p->key)
    {
        if (p->left == nullptr)
            p->left = new_n;
        else
            n_insert(p->left, new_n);
    }
    else
    {
        if (p->right == nullptr)
            p->right = new_n;
        else
            n_insert(p->right, new_n);
    }
}

Node *Tree::n_find(Node *p, int key)
{
    if (p->key == key)
        return p;
    else if (key < p->key)
        return n_find(p->left, key);
    else
        return n_find(p->right, key);
}

int main ()
{
    Tree G;

    G.print();

    Node *found = G.find_cycle(10);
    Node *found1 = G.find_cycle(5);
    cout << found->data << endl;
    cout << found1->data << endl;

    return EXIT_SUCCESS;
}