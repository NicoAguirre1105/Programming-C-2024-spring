#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class Queue
{
    private:
    double *collector;
    int size;
    int pointer;

    public:
    Queue (int x): size(x) 
    {
        collector = new double [size];
        pointer = 0;
    }

    bool empty()
    {
        return pointer == 0;
    }

    double pop()
    {
        if (this->empty())
        {
            cout << "ERROR: Queue is empty" << endl;
            return NULL;
        } else 
        {
            double x = collector[0];
            for (int i = 0; i < pointer - 1; i++)
            {
                collector[i] = collector[i + 1];
            }
            pointer--;
            return x;
        }
    }

    void push(double x)
    {
        if (pointer < size - 1)
        {
            collector[pointer] = x;
            pointer++;
        } else 
        {
            cout << "ERROR: Queue is full" << endl;
        }
    }
};

int main()
{
    Queue Q(7);
    cout << Q.empty() << endl;
    Q.push(10);
    cout << Q.empty() << endl;
    Q.push(155.2);
    cout << Q.pop() << endl;
    cout << Q.empty() << endl;
    cout << Q.pop() << endl;
    cout << Q.empty() << endl;

    return EXIT_SUCCESS;
}