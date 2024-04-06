#include <iostream>
#include <cstdlib>

using namespace std;

class Node 
{
    public:
    double data;
    double priority;
    Node *next;

    Node(double x, double p){
        this->data = x;
        this->priority = p;
        this->next = NULL;
    }
};

class Queue
{
    Node *head;
    Node *tail;

    public:
        Queue (): head(NULL), tail(NULL) {}
    
    void push (double x, double p = 0)
    {
        Node *temp = new Node(x, p);
        if (tail == NULL)
        {
            head = tail = temp;
            return;
        }
        Node *aux = head;
        Node *aux_prev = NULL;
        while(aux != NULL)
        {
            if (p > aux->priority)
            {
                temp->next = aux;
                if (aux != head)
                    aux_prev->next = temp;
                else
                    head = temp;
                return;
            }
            if (aux == tail)
            {
                tail->next = temp;
                tail = temp;
                return;
            }
            aux_prev = aux;
            aux = aux->next;
        }
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

int main () 
{
    Queue Q;

    cout << Q.empty() << endl;
    Q.push(5, 5);
    cout << Q.empty() << endl;
    Q.push(7);
    cout << Q.empty() << endl;
    Q.push(3,7);
    cout << Q.empty() << endl;
    cout << Q.pop() << endl;
    cout << Q.empty() << endl;
    cout << Q.pop() << endl;
    cout << Q.empty() << endl;
    cout << Q.pop() << endl;
    cout << Q.empty() << endl;

    return EXIT_SUCCESS;
}