#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

string sum (string s)
{
    string ans = s;
    int i;
    int l;
    int r;
    int x;
    int count = 0;

    while (s.find_first_of('+') != -1)
    {
        i = s.find_first_of('+');
        l = i;
        r = i;
        while(l - 1 >= 0 && isdigit(s[l - 1]))
        {
            l--;
        }

        while(r + 1 < s.size() && isdigit(s[r + 1]))
        {
            r++;
        }

        if(r == i || l == i)
        {
            s.erase(0, i + 1);
            count += i + 1;
        } else
        {
            x = stoi(s.substr(l, i - l)) + stoi(s.substr(i + 1, r - i));
            ans.erase(count + l, r - l + 1);
            s.erase(l, r - l + 1);
            ans.insert(count + l, to_string(x));
            s.insert(l, to_string(x));
        }

    }
    return ans;
}

int main ()
{
    string s;
    string ans;
    cout << "Insert string: ", cin >> s;

    ans = sum(s);
    cout << ans << endl;
    return EXIT_SUCCESS;
}