#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

int GCD(int a, int b)
{
    int r;
    while((a % b) > 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return b;
}

int LCM(int a, int b)
{
    int m = 0;
    int max = a >= b ? a : b;
    int min = a < b ? a : b;

    return (a/GCD(a, b))*b;
}

class Rational {
    public: 
    int dividend;
    int divisor;
    double result;

    Rational (): dividend(0), divisor(1), result(0) {}
    Rational (int x): dividend(x), divisor(1), result(x) {}
    Rational (int x, int y): dividend(x), divisor(y), result((double)x/y) 
    {
        this->simplify();
    }
    Rational (const Rational &p) = default;

    void simplify()
    {
        int m = GCD(abs(dividend), abs(divisor));
        dividend /= m;
        divisor /= m;
    }

    void print()
    {
        cout << dividend << " / " << divisor << " = " << result << endl;
    }

    ~Rational(){}

    Rational & operator = (const Rational & p)
    {
        if(this == &p) return *this;

        dividend = p.dividend;
        divisor = p.divisor;
        result = p.result;
        return *this;
    }
};

Rational operator+ (Rational p, Rational q)
{
    int m = LCM(abs(p.divisor), abs(q.divisor));
    int n1 = (m/p.divisor) * p.dividend;
    int n2 = (m/q.divisor) * q.dividend;

    Rational r (n1 + n2, m);
    return r;
}

Rational operator- (Rational p, Rational q)
{
    int m = LCM(p.divisor, q.divisor);
    int n1 = (m/p.divisor) * p.dividend;
    int n2 = (m/q.divisor) * (-1) * q.dividend;

    Rational r (n1 + n2, m);
    return r;
}

Rational operator* (Rational p, Rational q)
{
    cout << p.dividend * q.dividend << " " << p.divisor*q.divisor << endl;
    Rational r (p.dividend * q.dividend, p.divisor*q.divisor);
    return r;
}

Rational operator/ (Rational p, Rational q)
{
    Rational r (p.dividend * q.divisor, p.divisor * q.dividend);
    return r;
}

bool operator<= (Rational p , Rational q)
{
    return p.result <= q.result;
}

bool operator< (Rational p , Rational q)
{
    return p.result < q.result;
}

bool operator>= (Rational p , Rational q)
{
    return p.result >= q.result;
}

bool operator> (Rational p , Rational q)
{
    return p.result > q.result;
}

bool operator== (Rational p , Rational q)
{
    return p.result == q.result;
}

bool operator!= (Rational p , Rational q)
{
    return p.result != q.result;
}

int main()
{
    Rational p (20, 7);
    Rational q (22, 7);
    Rational r (-2, 5);
    Rational s = p / q;
    s.print();
    bool x = q < p;
    cout << boolalpha << x << endl; 
    return EXIT_SUCCESS;
}
