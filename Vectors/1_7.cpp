#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

void last_ocurre (vector <int> &v, vector <int> :: iterator & i, int N)
{
    vector <int> :: iterator i_aux;
    i_aux = find(v.begin(), v.end(), N);

    if(i_aux == v.end())
    {
        i = i_aux;
        cout << *i << '\n';
        return;
    }

    while (i_aux != v.end())
    {
        i = i_aux;
        i_aux = find(i_aux+1, v.end(), N);
    }
    cout << *i << '\n';
}

int main()
{
    vector <int> v;
    int n;
    int N;
    int counter = 0;
    int x;

    cout << "Number to find: ", cin >> N;
    
    cout << "Size: ", cin >> n;
    while (counter < n)
    {
        cout << "Enter data: ";
        cin >> x;
        v.push_back(x);
        counter++;
    }

    vector <int> :: iterator i;
    last_ocurre (v, i, N);
    cout << *i;

    return EXIT_SUCCESS;
}