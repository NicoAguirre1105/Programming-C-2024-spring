#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

string toBinary(int n)
{
    if(n == 0) return "0";
    else if (n == 1) return "1";
    else if (n % 2 == 0) return toBinary(n/2) + "0";
    else if (n % 2 != 0) return toBinary(n/2) + "1";
}

int digit(int x, int n)
{
    string b_x = toBinary(x);
    return int(b_x[n]);
}

int main()
{
    digit(5, 2);

    return EXIT_SUCCESS;
}