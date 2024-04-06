#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

void f1(stack<double> &S, char c)
{
    double first;
    double second;
    if (!S.empty())
    {
        second = S.top();
        S.pop();
    } else
    {
        cout << "Not enough values" << endl;
        exit(401);
    }

    if (!S.empty())
    {
        first = S.top();
        S.pop();
    } else {
        cout << "Not enough values" << endl;
        exit(401);
    }

    if (c == '*')
    {
        S.push(first * second);
    } else if (c == '/')
    {
        S.push(first / second);
    } else if (c == '+')
    {
        S.push(first + second);
    } else
    {
        S.push(first - second);
    }
}

void f1(stack<double> &S, double x)
{
    S.push(x);
}

void f2(stack<double> &S, stack<char> &Oper, char c = -1)
{
    static string str_num = "";
    if(isdigit(c))
    {
        str_num += c;
    }else 
    {
        if (str_num != "")
        {
            f1(S, (double)stoi(str_num));
            str_num = "";
        }

        if (c == -1)
        {
            while (!Oper.empty())
            {
                f1(S, Oper.top());
                Oper.pop();
            }
        } else if (c == '(')
        {
            Oper.push(c);
        } else if (c == ')')
        {
            while (Oper.top() != '(')
            {
                if (Oper.empty()) 
                {
                    cout << "Error with ()" << endl;
                    exit(401); 
                }
                f1(S, Oper.top());
                Oper.pop();
            }
            Oper.pop();
        } else if (c == '*' || c == '/')
        {
            while (!Oper.empty() && (Oper.top() == '*' || Oper.top() == '/'))
            {
                f1(S, Oper.top());
                Oper.pop();
            }
            Oper.push(c);
        } else if (c == '+' || c == '-')
        {
            while (!Oper.empty() && (Oper.top() == '*' || Oper.top() == '/' || Oper.top() == '+' || Oper.top() == '-'))
            {
                f1(S, Oper.top());
                Oper.pop();
            }
            Oper.push(c);
        } else 
        {
            cout << "Wrong operation" << endl;
            exit(401);
        }
    }
}

double result (stack<double> &S)
{
    double res = S.top();
    S.pop();
    if(S.empty())
        return res;
    return NULL;
}

int main() 
{
    stack <double> S;
    stack <char> Oper;
    char c;

    while (cin >> c)
    {
        f2(S, Oper, c);
    }
    f2(S, Oper);
    
    cout << result(S) << endl;

    return EXIT_SUCCESS;
}