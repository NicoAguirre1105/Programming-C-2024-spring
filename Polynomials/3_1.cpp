#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Polinomial
{
    public:
    vector<double> coeficient;
    int degree;

    Polinomial(): coeficient({0}), degree(0){}
    Polinomial (vector<double> v, int d): coeficient(v), degree(d) {}
    double & coef(int i)
    {
        static double error = -1;
        if (i <= degree && i >= 0)
        {
            return coeficient[i];
        }

        cout << "Out of range" << endl;
        return error;

    }

    double value(double x)
    {
        double ans = 0;
        double exp = 1;
        for(int i = 0; i <= degree; i++)
        {
            ans = ans + coeficient[i]*exp;
            exp *= x;
        }

        return ans;
    }

    ~Polinomial()
    {
        cout << "Deleted" << endl;
    }

    friend Polinomial operator+(Polinomial P, Polinomial Q);
};

Polinomial operator+ ( Polinomial P, Polinomial Q)
{
    int max_degree = P.degree > Q.degree ? P.degree : Q.degree;
    int min_degree = P.degree < Q.degree ? P.degree : Q.degree;
    vector <double> v (max_degree + 1, 0);
    Polinomial N (v, max_degree);
    for (int i = 0; i <= min_degree; i++)
    {
        N.coef(i) = P.coef(i) + Q.coef(i);
    }

    if (P.degree > Q.degree)
    {
        copy(P.coeficient.begin() + min_degree + 1, P.coeficient.end(), N.coeficient.begin() + min_degree + 1);
    } else if (P.degree < Q.degree)
    {
        copy(Q.coeficient.begin() + min_degree + 1, Q.coeficient.end(), N.coeficient.begin() + min_degree + 1);
    }

    return N;
}

Polinomial operator- ( Polinomial P, Polinomial Q)
{
    int max_degree = P.degree > Q.degree ? P.degree : Q.degree;
    int min_degree = P.degree < Q.degree ? P.degree : Q.degree;
    vector <double> v (max_degree + 1, 0);
    Polinomial N (v, max_degree);
    for (int i = 0; i <= min_degree; i++)
    {
        N.coef(i) = P.coef(i) - Q.coef(i);
    }

    if (P.degree > Q.degree)
    {
        copy(P.coeficient.begin() + min_degree + 1, P.coeficient.end(), N.coeficient.begin() + min_degree + 1);
    } else if (P.degree < Q.degree)
    {
        for (int i = min_degree + 1; i <= max_degree; i++)
        {
            N.coef(i) = -Q.coef(i);
        }
    }

    while (N.coef(N.degree) == 0 && N.degree >= 1)
    {
        N.coeficient.pop_back();
        N.degree--;
    }

    return N;
}

Polinomial operator* ( Polinomial P, Polinomial Q)
{
    vector <double> v (P.degree + Q.degree + 1, 0);
    Polinomial N (v, P.degree + Q.degree);
    for (int i = 0; i <= P.degree; i++)
    {
        for (int j = 0; j <= Q.degree; j++)
        {
            N.coef(i+j) += P.coef(i)*Q.coef(j);
        }
    }

    return N;
}

int main()
{
    vector<double> v1 {22, 4, 2};
    vector<double> v2 {2, 13, 2, 3, 1};

    Polinomial P (v1, v1.size() - 1);
    Polinomial Q (v2, v2.size() - 1);

    Polinomial N = P * Q;

    for (int i = 0; i <= N.degree; i++)
    {
        cout << N.coef(i) << ' ';
    }
    cout << endl;

    return EXIT_SUCCESS;
}