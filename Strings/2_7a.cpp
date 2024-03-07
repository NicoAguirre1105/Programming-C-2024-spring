#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int pos_var (string s)
{
    int i_start = s.find_first_of('{');
    int i_end = s.find_first_of('}');

    if(i_start == -1 && i_end == -1)
    {
        cout << s << endl;
        return EXIT_SUCCESS;
    }

    if(i_start == -1 || i_end == -1)
    {
        cout << "Not enough bracelets" << endl;
        return EXIT_FAILURE;
    }

    string ans;
    while (s.find_first_of(',') != -1)
    {
        ans = s.substr(0, i_start) + s.substr(i_start + 1, s.find_first_of(',') - i_start - 1) + s.substr(i_end + 1);
        cout << ans << endl;
        s.erase(i_start + 1, s.find_first_of(',') - i_start);
        i_end = s.find_first_of(' ');
    }
    s.erase(i_end, 1);
    s.erase(i_start, 1);
    cout << s << endl;
    return EXIT_SUCCESS;
}

int main ()
{
    string s;
    cout << "Insert string: ", cin >> s;

    pos_var(s);

    return EXIT_SUCCESS;
}