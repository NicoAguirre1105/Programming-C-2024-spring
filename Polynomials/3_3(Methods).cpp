#include <iostream>
#include <cstdlib>
#include <vector>
#include <initializer_list>

using namespace std;

class Polynomial
{
    public:
    double *coef;
    int degree;
    
    Polynomial (): coef(new double [1] {0}), degree(0){}
    Polynomial (double *pp, int d): coef(pp), degree(d) {}
    Polynomial (double x): coef(new double [1] {x}), degree(0) {}
    Polynomial (const initializer_list<double> & p):
        degree(p.size() - 1), coef(new double [p.size()]) 
        {
            copy(p.begin(), p.end(), coef);
        }
    Polynomial (const Polynomial & P) 
    {
        degree = P.degree;
        coef = new double[P.degree + 1];
        for (int i = 0; i <= P.degree; i++)
        {
            coef[i] = P.coef[i];
        } 
    }

    double value(double x)
    {
        double ans = 0;
        double exp = 1;
        for(int i = 0; i <= degree; i++)
        {
            ans = ans + coef[i]*exp;
            exp *= x;
        }

        return ans;
    }

    double & operator[] (int i)
    {
        static double c = -1;

        if(i >= 0 && i <= degree) return coef[i];
        else {
            cout << "Out of boundery" << endl;
            return c;
        }
    }

    Polynomial & operator = (const Polynomial & P)
    {
        if(this == &P) return *this;

        delete [] coef;
        degree = P.degree;
        coef = new double[degree];
        for (int i = 0;i <= degree; i++)
        {
            coef[i] = P.coef[i];
        }
        return *this;
    }

    void print()
    {
        for (int i = 0; i <= degree; i++)
        {
            cout << coef[i] << "\t";
        }
        cout << endl;
    }

    ~Polynomial()
    {
        cout << "Deleted" << endl;
    }

};

int main()
{
    double *list = new double[4] {21, 5, 2, 1};
    Polynomial empty;
    Polynomial P1 (list, 3);
    Polynomial P2 (3);
    Polynomial P3 {1, 2, 3, 4, 5};
    Polynomial P4 (P1);

    empty.print();
    P1.print();
    P2.print();
    P3.print();
    P4.print();
    cout << P3[2] << endl;

    return EXIT_SUCCESS;
}