#include <cstdlib>
#include <iostream>
#include <vector>

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

class Queue
{
    Node *head;
    Node *tail;

    public:
        Queue (): head(NULL), tail(NULL) {}
    
    void push (double x)
    {
        Node *temp = new Node(x);
        if (tail == NULL)
        {
            head = tail = temp;
            return;
        }
        tail->next = temp;
        tail = temp;
    }

    double pop()
    {
        if (head == NULL) return NULL;
        double value = head->data;
        Node *temp = head;
        head = head->next;
        if (head == NULL)
            tail = NULL;
        delete temp;
        return value;
    }

    bool empty()
    {
        return head == NULL;
    }
};

int main()
{
    Queue Q;

    cout << Q.empty() << endl;
    Q.push(5);
    cout << Q.empty() << endl;
    Q.push(3);
    cout << Q.empty() << endl;
    cout << Q.pop() << endl;
    cout << Q.empty() << endl;
    cout << Q.pop() << endl;
    cout << Q.empty() << endl;

    return EXIT_SUCCESS;
}