#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> :: iterator second_occure (vector <int> &v, int N)
{
    vector <int> :: iterator i;

    i = find(v.begin(), v.end(), N);
    if(i != v.end()) 
    {
        i = find(i+1, v.end(), N);
    }

    return i;
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
    i = second_occure (v, N);

    cout << *i;
    // Por que no se devuelve el valor fuera de la funcion

    return EXIT_SUCCESS;
}