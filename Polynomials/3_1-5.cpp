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

};

int main()
{
    vector<double> v1 {22, 4, 2};
    vector<double> v2 {2, 13, 2, 3, 1};

    Polinomial P (v1, v1.size() - 1);
    Polinomial Q (v2, v2.size() - 1);

    cout << P.coef(0) << endl;

    return EXIT_SUCCESS;
}