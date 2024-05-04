#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

struct Node
{
    int key;
    string data;
    Node *parent;
    Node *right;
    Node *left;
    Node(int k, string d, Node *l=nullptr, Node *r=nullptr): data(d), right(r), left(l), key(k) {
        if(left != nullptr)
            left->parent = this;
        
        if(right != nullptr)
            right->parent = this;
    }
    Node(): data(""), key(NULL), right(nullptr), left(nullptr) {}
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

void f_del(Node *&p)
{
    if (p == nullptr)
        return;
    
    f_del(p->left);
    f_del(p->right);
    delete p;
    p = nullptr;
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
            this->insert(new_n);
        }
        cout << endl;
    }

    ~Tree()
    {
        n_des(root);
    }

    void insert(Node *p)
    {
        if(root == nullptr)
        {
            root = p;
            return;
        }
        n_insert(root, p);
    }

    Node *find(int key)
    {
        return n_find(root, key);
    }

    void del_node(int key)
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

    bool check()
    {
        return n_check(root);
    }

    void del_max(int max)
    {
        Node *aux = root;
        Node *parent;
        while (1)
        {
            while (aux != nullptr && aux->key < max)
            {
                parent = aux;
                aux = aux->right;
            }

            if (aux == nullptr)
                return;
            
            f_del(aux->right);
            parent->right = aux->left;
            aux = parent->right;
        }     
    }

    void correct()
    {
        while (!check())
        {
            
            Node *wrong_parent = n_find_wrong(root);
            Node *wrong;
            bool inside = false;
            
            if (wrong_parent == nullptr)
                return;

            if(wrong_parent->left != nullptr)
            {
                if(wrong_parent->left->key >= wrong_parent->key)
                {
                    wrong = wrong_parent->left;
                    wrong_parent->left = nullptr;
                    inside = true;
                }
            } 

            if(!inside){
                wrong = wrong_parent->right;
                wrong_parent->right = nullptr;
            }
            n_insert(root, wrong);
        }
    }

    void find_range(int key, Node *&down_bound, Node *&up_bound)
    {
        Node *aux = root;
        down_bound = nullptr;
        up_bound = nullptr;

        while(aux != nullptr)
        {
            if (aux->key == key)
            {
                up_bound = aux;
                down_bound = aux;
                return;
            }

            if (aux->key > key)
            {
                if (up_bound == nullptr || (up_bound->key) > (aux->key))
                    up_bound = aux;

                aux = aux->left;
            } else 
            {
                if (down_bound == nullptr || (down_bound->key) < (aux->key))
                    down_bound = aux;
                aux = aux->right;
            }
        }
    }

    Node *next_key(Node *p)
    {
        Node *ans = p->parent;
        Node *aux = p->right;

        while (ans != nullptr)
        {
            if (ans->key > p->key)
                break;
            ans = ans->parent;
        }
        

        while (aux != nullptr)
        {
            ans = aux;
            aux = aux->left;
        }
        
        return ans;
    }

    private:
    static void n_insert(Node *p, Node *new_n);
    static Node *n_find(Node *p, int key);
    static void n_del_find(Node *&parent, Node *&aux, int key);
    static void n_find_last(Node *& last, Node *& last_parent);
    static void n_des(Node *&n);
    static bool n_check(Node *p);
    static Node *n_find_wrong(Node *p);
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

bool Tree::n_check(Node *p)
{
    if(p == nullptr)
        return true;
    
    if(p->left != nullptr)
        if(p->left->key >= p->key)
            return false;
    
    if(p->right != nullptr)
        if(p->right->key <= p->key)
            return false;
    
    return (n_check(p->left) && n_check(p->right));
}

Node *Tree::n_find_wrong(Node *p)
{
    if (p == nullptr)
        return nullptr;
    
    if(p->left != nullptr)
        if(p->left->key >= p->key)
            return p;
    
    if(p->right != nullptr)
        if(p->right->key <= p->key)
            return p;
    
    Node *aux = n_find_wrong(p->left);
    if (aux != nullptr)
        return aux;
    aux = n_find_wrong(p->right);
    if (aux != nullptr)
        return aux;
    return nullptr;
}

int main ()
{
    Node *p6 = new Node(8, "8"),
    *p9 = new Node(-10, "-10"),
    // *p8 = new Node(-2, "-2"),
     *p8 = new Node(-6, "-6"),
    *p7 = new Node(-5, "-5", p9, p8),
    *p10 = new Node(3, "3"),
    *p4 = new Node(7, "7", nullptr, p6),
    *p3 = new Node(10, "10", p4),
    *p1 = new Node (5, "5", nullptr, p3),
    *p5 = new Node(4, "4", p10, p1),
    *p2 = new Node(2, "2", p7, p5);

    Tree G(p2);

    G.correct();
    G.print();
    Node *up = nullptr;
    Node *down = nullptr;
    G.find_range(9, up, down);
    cout << up->key << " " << down->key << endl; 
    cout << G.next_key(p8)->key << endl;

    return EXIT_SUCCESS;
}