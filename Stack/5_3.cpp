#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

bool isNumber(string s)
{
    bool number = false;
    for(int i = 0; i < s.size(); i++)
    {
        if (!isdigit(s[i])) 
        {
            if (!number)
                return false;
            else
            {
                cout<< "Wrong input" << endl;
                exit(401);
            }
        }
        number = true;
    }
    return number;
}  

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

    double result()
    {
        double res = this->pop();
        if (this->empty())
        {
            return res;
        }
        cout << "An error has been found" << endl;
        return NULL;        
    }

    void f2(string s)
    {
        if(isNumber(s))
        {
            this->push(stoi(s));
        } else 
        {
            double first;
            double second;

            if (!this->empty())
                second = this->pop();
            else
            {
                cout << "Not enough values" << endl;
                exit(401);
            }

            if (!this->empty())
                first = this->pop();
            else
            {
                cout << "Not enough values" << endl;
                exit(401);
            }

            if (s == "*")
            {
                this->push(first * second);
            } else if (s == "/")
            {
                this->push(first / second);
            } else if (s == "+")
            {
                this->push(first + second);
            } else if (s == "-")
            {
                this->push(first - second);
            } else {
                cout << "Wrong operation" << endl;
                exit(401);
            }
        }
    }
};

 

int main () 
{
    Stack S;
    string s;

    while (cin >> s)
    {
        S.f2(s);
    }

    double x = S.result(); 

    cout << x << endl;
    
    return EXIT_SUCCESS;
}