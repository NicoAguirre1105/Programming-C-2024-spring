#include <iostream>
#include <cstdlib>

using namespace std;

struct UNode 
{
    double data;
    UNode *parent=nullptr;
    UNode *left;
    UNode *right;

    UNode (double d, UNode *l=nullptr, UNode *r=nullptr): data(d), left(l), right(r) 
    {
        if (l != nullptr)
        {
            left->parent = this;
        }
        if (r != nullptr)
        {
            right->parent = this;
        }
    }
};

void f_print(UNode* r, int indent = 1) 
{
    if (r == nullptr) return;
    f_print(r->right, indent + 3);
    for (int i = 0; i < indent; ++i)
        cout << ' ';
    cout << r->data << endl;
    f_print(r->left, indent + 3);
}

class UTree
{
    UNode *root;

    public:
    UTree (UNode *r): root(r) {}
    UTree (UTree &T)
    {
        root = n_copy(T.root);
    }

    void rotateLeft()
    {
        UNode *aux = root->right;
        root->right = aux->left;
        aux->left->parent = root;
        aux->left = root;
        root->parent = aux;
        aux->parent = nullptr;
        root = aux;
    }

    void deleteNode(UNode *p)
    {
        if (p == root)
        {
            if (p->left != nullptr)
            {
                root = p->left;
            } else 
            {
                root = p->right;
            }
            root->parent = nullptr;
            delete p;
            return;
        }

        UNode *parent = p->parent;
        UNode *newChild;
        bool dir_left;

        if (parent->left == p)
            dir_left = true;
        else
            dir_left = false;

        if(p->left != nullptr)
            newChild = p->left;
        else if (p->right != nullptr)
            newChild = p->right;
        else
        {
            if (dir_left)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            delete p;
            return;
        }
        newChild->parent = parent;
        if (dir_left)
            parent->left = newChild;
        else
            parent->right = newChild;
        delete p;
    }

    void print() // метод печати
    {
        f_print(root); // вызывает рекурсивную функцию
    }

    private:
    static UNode *n_copy(UNode *p);
};

UNode *UTree::n_copy(UNode *p)
{
    if (p == nullptr)
        return nullptr;
    UNode *q = new UNode(p->data, n_copy(p->left), n_copy(p->right));
    return q;
}

int main () 
{
    UNode *p6 = new UNode(6),
    *p7 = new UNode(7),
    *p8 = new UNode(8),
    *p5 = new UNode(5, p7),
    *p4 = new UNode(4),
    *p3 = new UNode(3, p6, p8),
    *p2 = new UNode(2, p4, p5),
    *p1 = new UNode (1, p2, p3);

    UTree T(p1);

    T.print();
    T.rotateLeft();
    T.print();
    T.deleteNode(p5);
    T.print();
    cout << p1->parent->data << " " << p6->parent->data << " " << (p3->parent == nullptr) << " " << p8->parent->data << endl;  

    UTree Q = T;
    Q.print();

    return EXIT_SUCCESS;
}