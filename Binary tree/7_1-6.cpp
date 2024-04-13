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

class BTree
{
    BNode *root;

    public:
    BTree (BNode *r): root(r) {}

    BNode *leftGrandchild() 
    {
        if (root == nullptr) return nullptr;
        if (root->left != nullptr && root->left->left != nullptr)
            return root->left->left;
        else if (root->left != nullptr && root->left->right != nullptr)
            return root->left->right;
        else if (root->right != nullptr && root->right->left != nullptr)
            return root->right->left;
        else if (root->right != nullptr && root->right->right != nullptr)
            return root->right->right;
        else
            return NULL;
    }

    BNode *leftVertex()
    {
        if (root->left == nullptr && root->right == nullptr)
            return NULL;
        BNode *aux = root;
        while (aux->left == nullptr && aux->right != nullptr)
        {
            aux = aux->right;
        }
        while (aux->left != nullptr)
        {
            aux = aux->left;
        }

        return aux;        
    }

    BNode *leftLeaf ()
    {
        if (root->left == nullptr && root->right == nullptr)
            return NULL;
        BNode *aux = root;
        while (1)
        {
            if (aux->left != nullptr)
            {
                aux = aux->left;
            } else if (aux->right != nullptr)
            {
                aux = aux->right;
            } else 
            {
                return aux;
            }
        }
    }

    void removeLeftLeaf()
    {
        if (root->left == nullptr && root->right == nullptr)
            return;
        BNode *aux = root;
        BNode *parent;
        bool last_move;
        while (1)
        {
            if (aux->left != nullptr)
            {
                parent = aux;
                aux = aux->left;
                last_move = true;
            } else if (aux->right != nullptr)
            {
                parent = aux;
                aux = aux->right;
                last_move = false;
            } else 
            {
                if (last_move)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
                delete aux; 
                return;               
            }
        }
    }

    BNode *second_LL()
    {
        stack<BNode*> search;

        if (root->left == nullptr && root->right == nullptr)
            return NULL;
        BNode *aux = root;
        BNode *last;
        bool first_found = false;
        while (!first_found)
        {
            if (aux->left != nullptr)
            {
                search.push(aux);
                aux = aux->left;
            } else if (aux->right != nullptr)
            {
                search.push(aux);
                aux = aux->right;
            } else 
            {
                first_found = true;
                last = aux;
            }
        }
        aux = search.top();
        while (1)
        {
            if (aux->left != nullptr && aux->left != last)
            {
                aux = aux->left;
            } else if (aux->right != nullptr && aux->right != last)
            {
                aux = aux->right;
            } else 
            {
                if (aux->left == nullptr && aux->right == nullptr)
                    return aux;
                else 
                {
                    last = aux;
                    search.pop();
                    aux = search.top();
                }
            }
        }

    }

    void rotateLeft()
    {
        BNode *aux = root->right;
        root->right = aux->left;
        aux->left = root;
        root = aux;
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
    *p2 = new BNode(2, nullptr, p5),
    *root = new BNode (1, p2, p3);

    BTree T(root);
    T.print();
    cout << T.leftLeaf()->data << endl;
    cout << T.second_LL()->data << endl;
    T.removeLeftLeaf();
    T.print();
    cout << T.leftVertex()->data << endl;
    cout << T.leftLeaf()->data << endl;
    T.rotateLeft();
    T.print();
    return EXIT_SUCCESS;
}