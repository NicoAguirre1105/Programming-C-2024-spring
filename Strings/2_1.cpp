#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

bool IP_validator (string s)
{
    int j;
    int x;
    string aux;
    for (int count = 0; count < 4; count++)
    {
        if (count == 3)
        {
            aux = s;
            // cout << "last: " << aux << endl;
        } else 
        {
            j = s.find_first_of('.');
            if (j == string::npos)
            {
                return false;
            }
            aux = s.substr(0, j);
            s = s.erase(0, j + 1);
        }

        for (char c : aux)
        {
            if(!isdigit(c)){
                return false;
            }
        }

        if(!(aux.size() > 0)) 
        {
            return false;
        }

        x = stoi(aux);
        if(x < 0 || x > 255)
        {
            return false;
        }        
    }

    return true;
}

int main()
{
    string s;
    bool is_correct = true;

    cout << "Insert IP-address: ", cin >> s;
    
    cout << "\n" << boolalpha << IP_validator(s) << "\n";

    return EXIT_SUCCESS;
}