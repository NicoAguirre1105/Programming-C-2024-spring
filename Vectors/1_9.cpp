#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

void last_ocurre (vector <int> v, vector <int> :: iterator & i, int N)
{
    i = upper_bound(v.begin(), v.end(), N);
    i--;
    if(*i != N) {
        cout << "Not found";
        i = v.end();
    } else {
        cout << "Found in " << (i - v.begin());
    }
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
    sort(v.begin(), v.end());
    last_ocurre (v, i, N);

    return EXIT_SUCCESS;
}