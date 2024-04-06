#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;

class Queue
{
    private:
        stack<double> AuxStack;
        stack<double> Stack;

    public:
        bool empty()
        {
            return Stack.empty();
        }

        double pop()
        {
            if(!this->empty())
            {
                double x = Stack.top();
                Stack.pop();
                return x;
            }
            cout << "ERROR: Queue is empty" << endl;
            return NULL;
        }

        void push(double p)
        {
            double x;
            while (!Stack.empty())
            {
                x = Stack.top();
                Stack.pop();
                AuxStack.push(x);
            }
            Stack.push(p);
            while (!AuxStack.empty())
            {
                x = AuxStack.top();
                AuxStack.pop();
                Stack.push(x);
            }
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
    cout << Q.pop() << endl;


    return EXIT_SUCCESS;
}