#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

string find_pattern(string s, string pat)
{
    string new_s = s;
    int n = pat.size();
    int i = s.find(pat);
    int aux = 0;
    while(i != -1)
    {

        s = s.erase(0, i + n);
        new_s.insert(i + aux, "(");
        new_s.insert(i + aux + n + 1, ")");
        aux += i + n + 2;
        i = s.find(pat);
    }

    return new_s;
}

int main ()
{
    string s;
    string pat;

    cout << "Insert string: ", cin >> s;
    cout << "Insert pattern: ", cin >> pat;

    s = find_pattern(s, pat);

    cout << s;
    return EXIT_SUCCESS;
}