#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int find_bracket (string s, int i_start)
{
    int count = 0;
    string sub_s = s.substr(i_start + 1);
    for (int i = 0; i < sub_s.size(); i++)
    {
        if(sub_s[i] == '{')
        {
            count += 1;
            continue;
        } 
        if (sub_s[i] == '}')
        {
            if (count == 0) 
            {
                return i + i_start + 1;
            }
            count -= 1;
        }
    }

    return -1;
}

int find_comma (string s, int i_start, int i_end)
{
    int count = 0;
    string sub_s = s.substr(i_start + 1);
    for (int i = 0; i < i_end - i_start; i++)
    {
        if(sub_s[i] == '{')
        {
            count += 1;
            continue;
        } 
        if (sub_s[i] == '}')
        {
            count -= 1;
            continue;
        }
        if (sub_s[i] == ',' && count == 0) 
        {
            return i + i_start + 1;
        }
    }

    return -1;
}

int print_var (string s)
{
    int i_start = s.find_first_of('{');
    int i_end = find_bracket(s, i_start);

    if(i_start == -1 && i_end == -1)
    {
        cout << s << endl;
        return EXIT_SUCCESS;
    }

    if(i_start == -1 || i_end == -1)
    {
        cout << "Not enough brackets" << endl;
        return EXIT_FAILURE;
    }

    // TODO: Buscar la primera coma que valga y de ahi pasar a la funcion la parte izquierda, derecha, y centro
    string ans;
    int comma_index = find_comma(s, i_start, i_end);
    while (comma_index != -1)
    {
        ans = s.substr(0, i_start) + s.substr(i_start + 1, comma_index - i_start - 1) + s.substr(i_end + 1);
        print_var(ans);
        i_end -= comma_index - i_start;
        s.erase(i_start + 1, comma_index - i_start);
        comma_index = find_comma(s, i_start, i_end);
    }
    s.erase(i_end, 1);
    s.erase(i_start, 1);
    print_var(s);
    return EXIT_SUCCESS;
}

int main ()
{
    string s;
    cout << "Insert string: ", cin >> s;

    print_var(s);

    return EXIT_SUCCESS;
}