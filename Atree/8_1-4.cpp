#include <cstdlib>
#include <iostream>

using namespace std;

template<class T>
struct ANode 
{
    T data;
    ANode<T> *right, *down;
    ANode(T dd, ANode<T> *d = nullptr, ANode<T> *r = nullptr):
    data(dd), down(d), right(r) {}
};

template<class T>
void f_print(ANode<T> *p, int d = 0)
{
    if (p == nullptr) return;
    for (int i = 0; i < d; i++)
        cout << ' ';
    cout << p->data << endl;
    f_print(p->down, d + 3);
    f_print(p->right, d);
}

template<class T>
int countChildren (ANode<T> *p)
{
    int c = 0;
    if (p == nullptr) return c;
    p = p->down;
    while (p != nullptr)
    {
        c++;
        p = p->right;
    }
    return c;
}

template<class T>
int countGChildren (ANode<T> *p)
{
    int c = 0;
    if (p == nullptr) return c;
    p = p->down;
    while (p != nullptr)
    {
        c += countChildren(p);
        p = p->right;
    }
    return c;
}

template<class T>
ANode<T> *find(ANode<T> *p, T d)
{
    ANode<T> *temp;
    if (p->down == nullptr) return nullptr;
    temp = p->down;
    while (temp != nullptr)
    {
        if (temp->data == d)
            return temp;
        temp = temp->right;
    }
    return nullptr;
    
}

template <class T>
void del_children(ANode<T> *p)
{
    ANode<T> *t, *t1, *last_child, *new_child;
    t = p->down;
    new_child = t->down;
    p->down = new_child;
    while (t->right != nullptr)
    {
        t1 = t;
        last_child = new_child;
        while (last_child->right != nullptr)
            last_child = last_child->right;
        t = t->right;
        new_child = t->down;
        last_child->right = new_child;
        delete t1;
    }
}

template<class T>
class ATree
{
    ANode<T> *root;
    public:
    ATree(ANode<T> *p): root(p) {}

    void print()
    {
        f_print(root);
    }

    void add_first(T d)
    {
        ANode<T> *t;
        t = new ANode<T> (d, nullptr, root->down);
        root->down = t;
    }

    void del_first()
    {
        ANode<T> *t, *t1, *t2;
        t1 = root->down;
        t2 = t1->right;
        t = t2;
        while (t->right != 0)
            t = t->right;
        t->right = t1->right;
        root->down = t2;
        delete t1;
    }

    ANode<T> *find_spec(T d1, T d2)
    {
        ANode<T> *p, *temp;
        p = root;
        if(p->down == nullptr) return nullptr;
        p = p->down;
        while (p != nullptr)
        {
            if (p->data == d1 && p->down != nullptr)
            {
                temp = p->down;
                while (temp != nullptr)
                {
                    if (temp->data == d2)
                        return p;
                    temp = temp->right;
                }
            }
            p = p->right;
        }
        cout << "There isn't that node" << endl;
        return nullptr;
    }

    ANode<T> *find_seq(ANode<T> *p, T *seq, int size, int i)
    {
        ANode<T> *temp, *t1;
        temp = p->down;
        while(temp != nullptr)
        {
            if (temp->data == seq[i])
            {
                if (size  > i + 1)
                {
                    t1 = find_seq(temp, seq, size, i + 1);
                    if (t1 != nullptr)
                        return t1;
                } else return temp;
            }
            temp = temp->right;
        }
        return nullptr;
    }

    ANode<T> *find_sequence(T *seq, int size)
    {
        ANode<T> *t, *temp;
        t = root->down;
        while (t != nullptr)
        {
            if (t->data == seq[0])
            {
                if (size > 1)
                {
                    temp = find_seq(t, seq, size, 1);
                    if (temp != nullptr)
                        return temp;
                } else return t;                
            }
            t = t->right;
        }
        return nullptr;
    }
};

int main()
{
    ANode <int> *p10 = new ANode <int> (10),
        *p11 = new ANode <int> (11),
        *p88 = new ANode <int> (8, p11, p10),
        *p9 = new ANode <int> (9, nullptr, p88),
        *p8 = new ANode <int> (8),
        *p7 = new ANode <int> (7),
        *p6 = new ANode <int> (6, nullptr, p7),
        *p5 = new ANode <int> (5, nullptr, p6),
        *p4 = new ANode <int> (3, p9),
        *p3 = new ANode <int> (3, p8, p4),
        *p2 = new ANode <int> (2, p5, p3),
        *p1 = new ANode <int> (1, p2);
    
    ATree<int> T(p1);
    int *seq;
    seq = new int [3] {3, 8, 11};
    T.print();

    cout << countGChildren(p1) << endl;
    cout << T.find_spec(3, 8)->data << ' ' << T.find_spec(3,8)->down->data << endl;
    cout << T.find_sequence(seq, 3)->data << endl;
    del_children(p1);
    T.print();
    return EXIT_SUCCESS;
}