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
    Polynomial (double p, int d): 
        coef(new double [d + 1] {0}), degree(d)
        {
            coef[degree] = p;
        }
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
    Polynomial (Polynomial && P): coef(P.coef), degree(P.degree)
    {
        P.coef = nullptr;
        P.degree = 0;
    }

    double & operator[] (int i) const
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

    double operator () (double x) const
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

    Polynomial & operator = (Polynomial && P)
    {
        if(this == &P) return *this;

        delete [] coef;
        degree = P.degree;
        coef = P.coef;

        P.coef = nullptr;
        P.degree = 0;

        return *this;
    }

    void minimize()
    {
        while (coef[degree] == 0 && degree >= 1)
        {
            degree--;
        }
    }

    ~Polynomial(){}

    friend Polynomial operator+(Polynomial P, Polynomial Q);
    friend Polynomial operator*(Polynomial P, Polynomial Q);
    friend Polynomial operator-(Polynomial P, Polynomial Q);
    friend Polynomial operator/(Polynomial P, Polynomial Q);
    friend Polynomial operator%(Polynomial P, Polynomial Q);
};


Polynomial operator+ ( Polynomial P, Polynomial Q)
{
    int max_degree = P.degree > Q.degree ? P.degree : Q.degree;
    int min_degree = P.degree < Q.degree ? P.degree : Q.degree;
    double *list =  new double[max_degree + 1] {0};
    Polynomial N (list, max_degree);
    for (int i = 0; i <= min_degree; i++)
    {
        N[i] = P[i] + Q[i];
    }

    if (P.degree > Q.degree)
    {
        for (int i = min_degree + 1; i <= max_degree; i++)
        {
            N[i] = P[i];
        }
    } else if (P.degree < Q.degree)
    {
        for (int i = min_degree + 1; i <= max_degree; i++)
        {
            N[i] = Q[i];
        }
    }

    return move(N);
}

Polynomial operator- ( Polynomial P, Polynomial Q)
{
    int max_degree = P.degree > Q.degree ? P.degree : Q.degree;
    int min_degree = P.degree < Q.degree ? P.degree : Q.degree;
    double *list =  new double[max_degree + 1] {0};
    Polynomial N (list, max_degree);
    for (int i = 0; i <= min_degree; i++)
    {
        N[i] = P[i] - Q[i];
    }

    if (P.degree > Q.degree)
    {
        for (int i = min_degree + 1; i <= max_degree; i++)
        {
            N[i] = P[i];
        }
    } else if (P.degree < Q.degree)
    {
        for (int i = min_degree + 1; i <= max_degree; i++)
        {
            N[i] = -Q[i];
        }
    }

    N.minimize();

    return N;
}

Polynomial operator* ( Polynomial P, Polynomial Q)
{
    double *list =  new double[P.degree + Q.degree + 1] {0};
    Polynomial N (list, P.degree + Q.degree);
    for (int i = 0; i <= P.degree; i++)
    {
        for (int j = 0; j <= Q.degree; j++)
        {
            N[i + j] += P[i] * Q[j];
        }
    }

    return N;
}

Polynomial operator/ ( Polynomial P, Polynomial Q) 
{
    // Comparison

    if(P.degree < Q.degree)
    {
        Polynomial N;
        return N;
    }

    // Division
    double new_coef = P[P.degree]/Q[Q.degree];
    double new_degree = P.degree - Q.degree;
    Polynomial T (new_coef, new_degree);
    Polynomial N1 = P - (T * Q);
    N1.minimize();
    Polynomial N = N1 / Q;
    return T + N;
}

Polynomial operator% (Polynomial P, Polynomial Q)
{
    Polynomial N = P - (P / Q) * Q;
    N.minimize();
    return N;
}

ostream & operator << (ostream &st, Polynomial P)
{
    bool first_term = true;
    for (int i = 0; i <= P.degree; i++)
    {
        if (P[i] == 0) 
            continue;
        if (!first_term)
        {
            if(P[i] < 0)
                st << " - ";
            else
                st << " + ";
        } else first_term = false;

        if (P[i] != 1)
        {
            if(P[i] > 0)
                st << P[i];
            else
                st << -P[i];
        }
        if (i != 0)
            st << "x";
        if (i > 1)
            st << "^" << i;
    }
    st << endl;
    return st;
}

istream & operator >> (istream &st, Polynomial P)
{ 
    double x;
    int count = 0;
    Polynomial aux;
    P = aux;
    while (cout << "Insert coefficient for x^" << count << ": ", st >> x)
    {
        Polynomial Q (x, count);
        P = P + Q;
        count++;
    }
    st.clear();
    return st;
}

int main()
{
    Polynomial P {0, 1, 0, 2};
    Polynomial Q {-9, 3};

    cout << Q[1] << endl;
    Q[1] = 5;
    cout << Q[1] << endl;

    return EXIT_SUCCESS;
}