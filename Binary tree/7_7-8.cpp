#include <iostream>
#include <cstdlib>

using namespace std;

struct BNode 
{
    double data;
    BNode *parent=nullptr;
    BNode *left;
    BNode *right;

    BNode (double d, BNode *l=nullptr, BNode *r=nullptr): data(d), left(l), right(r) 
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

void f_print(BNode* r, int indent = 1) 
{
    if (r == nullptr) return;
    f_print(r->right, indent + 3);
    for (int i = 0; i < indent; ++i)
        cout << ' ';
    cout << r->data << endl;
    f_print(r->left, indent + 3);
}

class BTree
{
    BNode *root;

    public:
    BTree (BNode *r): root(r) {}

    void rotateLeft()
    {
        BNode *aux = root->right;
        root->right = aux->left;
        aux->left->parent = root;
        aux->left = root;
        root->parent = aux;
        aux->parent = nullptr;
        root = aux;
    }

    void deleteNode(BNode *p)
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

        BNode *parent = p->parent;
        BNode *newChild;
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
};

int main () 
{
    BNode *p6 = new BNode(6),
    *p7 = new BNode(7),
    *p8 = new BNode(8),
    *p5 = new BNode(5, p7),
    *p4 = new BNode(4),
    *p3 = new BNode(3, p6, p8),
    *p2 = new BNode(2, p4, p5),
    *p1 = new BNode (1, p2, p3);

    BTree T(p1);

    T.print();
    T.rotateLeft();
    T.print();
    T.deleteNode(p5);
    T.print();
    cout << p1->parent->data << " " << p6->parent->data << " " << (p3->parent == nullptr) << " " << p8->parent->data << endl;  

    return EXIT_SUCCESS;
}