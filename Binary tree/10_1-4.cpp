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
        cout << endl;
    }

    ~Tree()
    {
        n_des(root);
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

    void del_node_cycle(int key)
    {
        Node *aux = root;
        Node *parent;
        bool found = false;

        while (aux != nullptr)
        {
            if (aux->key == key)
            {
                found = true;
                break;
            } else if (key < aux->key)
            {
                parent = aux;
                aux = aux->left;
            } else
            {
                parent = aux;
                aux = aux->right;
            }
        }

        if (!found)
            cout << "Key not found" << endl;

        if (aux == root)
        {
            if (aux->right == nullptr && aux->left == nullptr)
                root = nullptr;
            else if (aux->right == nullptr)
                root = aux->left;
            else if (aux->left == nullptr)
                root = aux->right;
            else
            {
                Node *last_parent;
                Node *last;
                last = aux->right;
                while (last->left != nullptr)
                {
                    last_parent = last;
                    last = last->left;
                }
                
                root = last;

                if (last_parent->left == last)
                    last_parent->left = last->right;
                else
                    last_parent->right = last->right;

                last->right = aux->right;
                last->left = aux->left;
            }
            delete aux;
            return;
        }

        if (aux->right == nullptr && aux->left == nullptr)
        {
            if (parent->left == aux)
                parent->left = nullptr;
            else
                parent->right = nullptr;
        } else if (aux->right == nullptr)
        {
            if (parent->left == aux)
                parent->left = aux->left;
            else
                parent->right = aux->left;
        } else if (aux->left == nullptr)
        {
            if (parent->left == aux)
                parent->left = aux->right;
            else
                parent->right = aux->right;
        } else
        {
            Node *last_parent;
            Node *last;
            last = aux->right;
            while (last->left != nullptr)
            {
                last_parent = last;
                last = last->left;
            }
            
            if (parent->left == aux)
                parent->left = last;
            else
                parent->right = last;

            if (last_parent->left == last)
                last_parent->left = last->right;
            else
                last_parent->right = last->right;

            last->right = aux->right;
            last->left = aux->left;
        }
        delete aux;
    }

    Node *find_rec(int key)
    {
        return n_find(root, key);
    }

    void del_node_rec(int key)
    {
        Node *parent;
        Node *aux = root;
        n_del_find(parent, aux, key);
        Node *last_parent;
        Node *last = aux->right;
        n_find_last(last, last_parent);
        if (parent->left == aux)
            parent->left = last;
        else
            parent->right = last;

        if (last_parent->left == last)
            last_parent->left = last->right;
        else
            last_parent->right = last->right;
    
        last->left = aux->left;
        last->right = aux->right;
        delete aux;
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
    static void n_del_find(Node *&parent, Node *&aux, int key);
    static void n_find_last(Node *& last, Node *& last_parent);
    static void n_des(Node *&n);
};

void Tree::n_des(Node *&n)
{
    if (n == nullptr)
        return;
    n_des(n->left);
    n_des(n->right);
    delete n;
}

void Tree::n_find_last(Node *& last, Node *& last_parent)
{
    if (last->left != nullptr)
    {
        last_parent = last;
        last = last->left;
        n_find_last(last, last_parent);
    }
}

void Tree::n_del_find(Node *&parent, Node *&aux, int key)
{
    if (aux == nullptr)
    {
        cout << "Key not found" << endl;
        exit(-1);
    }

    if (aux->key == key)
        return;
    else if (key < aux->key)
    {
        parent = aux;
        aux = aux->left;
    } else
    {
        parent = aux;
        aux = aux->right;
    }
    n_del_find(parent, aux, key);
}

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
    if (p == nullptr)
    {
        cout << "Not found" << endl;
        return nullptr;
    }
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

    // Node *found = G.find_rec(10);
    // Node *found1 = G.find_rec(5);
    // cout << found->data << endl;
    // cout << found1->data << endl;
    G.del_node_cycle(2);
    G.print();

    return EXIT_SUCCESS;
}