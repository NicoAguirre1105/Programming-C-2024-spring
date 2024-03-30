#include <cstdlib>
#include <iostream>

using namespace std;

class Node 
{
    public:
    double data;
    Node *next;

    Node(double x){
        this->data = x;
        this->next = NULL;
    }
};

class Stack
{
    Node *head;

    public:
    Stack (): head(NULL) {}
    
    double pop()
    {
        Node *temp;
        double value;
        if (head != NULL) {
            temp = head;
            value = head->data;
            head = head->next;
            delete temp;
            return value;
        }
        return NULL;
    }

    void push(double x)
    {
        Node *temp = new Node(x);
        temp->data = x;
        temp->next = head;
        head = temp;
    }

    bool empty()
    {
        return head == NULL;
    }
};


int main () 
{
    Stack S;
    S.push(2);
    S.push(3);
    S.push(4);
    
    cout << S.pop() << " " << S.pop() << endl;
    cout << S.empty() << " " << S.pop() << " " << S.empty() << endl;
    S.push(7);
    cout << S.empty() << " " << S.pop() << endl;

    return EXIT_SUCCESS;
}