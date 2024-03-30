#include <cstdlib>
#include <iostream>
#include <initializer_list>

using namespace std;

class Stack
{
    private:
    double *collector;
    int size;

    public:
    Stack (): collector(new double [0]), size(0) {}
    Stack (double *c, int s): collector(c), size(s) {}
    Stack (const initializer_list<double> &c): 
        collector(new double [c.size()]),
        size(c.size()) 
        {
            copy(c.begin(), c.end(), collector);
        }

    double pop()
    {
        if (size > 0) {
            size--;
            return collector[size];
        }
        return NULL;
    }

    void push(double x)
    {
        collector[size] = x;
        size++;
    }

    bool empty()
    {
        return !(size > 0);
    }
};


int main () 
{
    Stack S {1,3,4};
    
    cout << S.pop() << " " << S.pop() << endl;
    cout << S.empty() << " " << S.pop() << " " << S.empty() << endl;
    S.push(7);
    cout << S.empty() << " " << S.pop() << endl;

    return EXIT_SUCCESS;
}