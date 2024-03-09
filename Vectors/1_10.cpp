#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

void binary (vector <double> v, int & left, int & right, double N)
{
    if (left > right) {
        int aux = left;
        left = right;
        right = aux;
        return;
    }

    int mid_index = (left + right)/2;

    if (v[mid_index] == N)
    {
        left = mid_index - 1;
        right = mid_index + 1;
        return;
    }else if (v[mid_index] < N)
    {
        left = mid_index + 1;
        binary(v, left, right, N);
    } else 
    {
        right = mid_index - 1;
        binary(v, left, right, N);
    }
}

int main()
{
    vector <double> v;
    int n;
    double N;
    double x;

    cout << "Size: ", cin >> n;
    while (n > 0)
    {
        cout << "Value: ", cin >> x;
        v.push_back(x);
        n--;
    }
    cout << "\n";
    cout << "Number to find: ", cin >> N;

    sort(v.begin(), v.end());

    int i = 0;
    int j = v.size() - 1;

    binary(v, i, j, N);
    cout << i << " " << j;

    return EXIT_SUCCESS;
}