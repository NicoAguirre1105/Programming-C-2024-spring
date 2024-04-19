#include <iostream>
#include <cstdlib>
#include <stack>
#include <vector>

using namespace std;

struct BNode 
{
    double data;
    BNode *left;
    BNode *right;
 
    BNode (double x, BNode *l=nullptr, BNode *r=nullptr): data(x), left(l), right(r) {}
};

double BTree::n_sum(BNode *p)
{
    if (p == nullptr)
        return 0;
    return p->data + n_sum(p->left) + n_sum(p->right);
}

int BTree::n_neg_count(BNode *p)
{
    if (p == nullptr)
        return 0;
    if (p->data < 0)
        return 1 + n_neg_count(p->left) + n_neg_count(p->right);
    else
        return 0 + n_neg_count(p->left) + n_neg_count(p->right);
}

int BTree::n_height(BNode *p)
{
    if (p == nullptr)
        return 0;
    
    int x1 = n_height(p->left);
    int x2 = n_height(p->right);

    return x1 >= x2 ? x1 + 1 : x2 + 1;
}

void BTree::n_reflect(BNode *p)
{
    if (p == nullptr)
        return;
    
    n_reflect(p->left);
    n_reflect(p->right);

    BNode *aux = p->left;
    p->left = p->right;
    p->right = aux;
}

double n_mult(BNode *p)
{
    if (p == nullptr || p->left == nullptr || p->right == nullptr)
        return 0;

    return p->left->data * p->right->data;
}

double BTree::n_eval(BNode *p)
{
    if (p->left == nullptr)
        return p->data;
    
    if (p->data == 1)
        return n_eval(p->left) + n_eval(p->right);
    else if (p->data == 2)
        return n_eval(p->left) - n_eval(p->right);
    else if (p->data == 3)
        return n_eval(p->left) * n_eval(p->right);
    else if (p->data == 4)
        return n_eval(p->left) / n_eval(p->right);
    else
    {
        cout << "Wrong operation" << endl;
        exit(-1);
    }
}

BNode* BTree::n_find(BNode *p, double x)
{
    if (p == nullptr)
        return nullptr;

    if(p->data == x)
        return p;

    BNode *aux = n_find(p->left, x);
    if (aux != nullptr)
        return aux;
    aux = n_find(p->right, x);
    if (aux != nullptr)
        return aux;
    
    return nullptr;
}

double BTree::n_min(BNode *p)
{
    if (p->left != nullptr && p->right != nullptr)
    {
        double x1 = n_min(p->left);
        double x2 = n_min(p->right);

        double x_min = x1 <= x2 ? x1 : x2;

        return p->data <= x_min ? p->data : x_min;
    } else if (p->left != nullptr)
    {
        double x = n_min(p->left);

        return p->data <= x ? p->data : x;
    } else if (p->right != nullptr)
    {
        double x = n_min(p->right);
        
        return p->data <= x ? p->data : x;
    } else
    {
        return p->data;
    }
}

void BTree::fprint(BNode* r, int indent = 1) 
{
    if (r == nullptr) return;
    fprint(r->right, indent + 3);
    for (int i = 0; i < indent; ++i)
        cout << ' ';
    cout << r->data << endl;
    fprint(r->left, indent + 3);
}

class BTree
{
    BNode *root;

    public:
    BTree (BNode *r): root(r) {}

    void print() // метод печати
    {
        fprint(root); // вызывает рекурсивную функцию
    }

    double sum()
    {
        return n_sum(root);
    }

    int neg_count()
    {
        return n_neg_count(root);
    }

    int height()
    {
        return n_height(root);
    }

    void reflect()
    {
        n_reflect(root);
    }

    double eval()
    {
        return n_eval(root);
    }

    BNode* find(double x)
    {
        return n_find(root, x);
    }

    double min()
    {
        return n_min(root);
    }

    private:
    static void fprint(BNode *p, int indent = 1);
    static double n_sum(BNode *p);
    static int n_neg_count(BNode *p);
    static int n_height(BNode *p);
    static void n_reflect(BNode *p);
    static double n_eval(BNode *p);
    static BNode* n_find(BNode *p, double x);
    static double n_min(BNode *p);
};

int main ()
{       
    BNode *p6 = new BNode(6),
    *p7 = new BNode(-2),
    *p8 = new BNode(8),
    *p5 = new BNode(5),
    *p4 = new BNode(4),
    *p3 = new BNode(2, p6, p8),
    *p2 = new BNode(2, p7, p5),
    *root = new BNode (1, p2, p3);

    BTree T(root);

    T.print();
    cout << T.sum() << endl;
    cout << T.neg_count() << endl;
    cout << T.height() << endl;
    T.reflect();
    T.print();
    cout << n_mult(root) << endl;
    cout << T.eval() << endl;
    cout << T.min() << endl;

    BNode *found = T.find(4);
    if (found == nullptr)
    {
        cout << "nullptr" << endl;
    } else
    {
        cout << found->data << " " << found->left->data << " " << found->right->data << endl; 
    }

    return EXIT_SUCCESS;
}