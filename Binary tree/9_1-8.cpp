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

void f_print(BNode* r, int indent = 1) 
{
    if (r == nullptr) return;
    f_print(r->right, indent + 3);
    for (int i = 0; i < indent; ++i)
        cout << ' ';
    cout << r->data << endl;
    f_print(r->left, indent + 3);
}

void f_del(BNode *&p)
{
    if (p == nullptr)
        return;
    
    f_del(p->left);
    f_del(p->right);
    delete p;
    p = nullptr;
}

class BTree
{
    BNode *root;

    public:
    BTree (BNode *r): root(r) {}
    BTree (BTree &T) 
    {
        root = n_copy(T.copy());
    }

    void print()
    {
        f_print(root);
        cout << "----------------" << endl;
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

    double mult()
    {
        return n_mult(root);
    }

    BNode* copy()
    {
        return n_copy(root);
    }

    double alt_sum()
    {
        return n_alt_sum(root);
    }

    void del0()
    {
        n_del0(root);
    }

    void del_leaves()
    {
        n_del_l(root);
    }

    void enlarge(int d)
    {
        n_enlarge(root, d);
    }

    void del1()
    {
        n_del1(root);
    }

    private:
    static double n_sum(BNode *p);
    static int n_neg_count(BNode *p);
    static int n_height(BNode *p);
    static void n_reflect(BNode *p);
    static double n_eval(BNode *p);
    static double n_mult(BNode *p);
    static BNode* n_find(BNode *p, double x);
    static double n_min(BNode *p);
    static BNode* n_copy(BNode *p);
    static double n_alt_sum(BNode *p);
    static void n_del0(BNode *&p);
    static void n_del_l(BNode *&p);
    static void n_enlarge(BNode *&p, int d);
    static void n_del1(BNode *&p);
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

double BTree::n_mult(BNode *p)
{
    if (p->left == nullptr || p->right == nullptr)
        return 1;

    return p->data * n_mult(p->left) * n_mult(p->right);
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

BNode *BTree::n_copy(BNode *p)
{
    if (p == nullptr)
        return nullptr;

    BNode *q = new BNode(p->data, n_copy(p->left), n_copy(p->right));
    return q;
}

double BTree::n_alt_sum(BNode *p)
{
    if (p == nullptr)
        return 0;
    
    if (p->left == nullptr && p->right == nullptr)
        return p->data;
    
    return n_alt_sum(p->left) - n_alt_sum(p->right);
}

void BTree::n_del0(BNode *&p)
{
    if (p == nullptr)
        return;
    
    if (p->data == 0)
    {
        f_del(p);
        return;
    }
    n_del0(p->left);
    n_del0(p->right);
}

void BTree::n_del_l(BNode *&p)
{
    if (p == nullptr)
        return;
    if (p->left == nullptr && p->right == nullptr)
    {
        f_del(p);
        return;
    }
    n_del_l(p->left);
    n_del_l(p->right);
}

void BTree::n_enlarge(BNode *&p, int d)
{
    if (p != nullptr)
    {
        n_enlarge(p->left, d);
        n_enlarge(p->right, d);
        return;
    }
    p = new BNode(d);
}

void BTree::n_del1(BNode *&p)
{
    if (p == nullptr)
        return;
    if (p->data == 1)
    {
        f_del(p->left);
        p = p->right;
        n_del1(p);
        return;
    }
    n_del1(p->right);
    n_del1(p->left);
}

int main ()
{       
    BNode *p6 = new BNode(6),
    *p9 = new BNode(9),
    *p8 = new BNode(8),
    *p7 = new BNode(1, p9, p8),
    *p10 = new BNode(10),
    *p5 = new BNode(5, p10),
    *p4 = new BNode(4),
    *p3 = new BNode(3, p6),
    *p2 = new BNode(2, p7, p5),
    *root = new BNode (100, p2, p3);

    BTree T(root);

    T.print();
    T.del1();
    T.print();
    T.enlarge(7);
    return EXIT_SUCCESS;
}