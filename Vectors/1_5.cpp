#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

void repeat (vector <double> v, int n, vector <double> & v_new)
{
    int N = v.size();
    for(int i = 0; i < n; i++)
    {
        copy(v.begin(), v.end(), v_new.begin() + i*N);
    }

    cout << endl;
    vector <double > :: iterator i;
    for (i = v_new.begin(); i != v_new.end(); i++)
    {
        cout << *i << ' ';
    }
}

int main()
{
    vector <double> v;
    int n;
    int N;
    int counter = 0;
    double x;

    cout << "Repeat times: ", cin >> N;
    if (N <= 0)
    {
        return EXIT_FAILURE;
    }
    
    cout << "Size: ", cin >> n;
    while (counter < n)
    {
        cout << "Enter data: ";
        cin >> x;
        v.push_back(x);
        counter++;
    }

    vector <double> v_new(N*v.size());
    repeat(v, N, v_new);

    return EXIT_SUCCESS;
}