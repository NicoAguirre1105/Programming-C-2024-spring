#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

void concat (vector <double> v1, vector <double> v2, vector <double> v)
{
    copy(v1.begin(), v1.end(), v.begin());
    copy(v2.begin(), v2.end(), v.begin() + v1.size());

    cout << endl;
    vector <double > :: iterator i;
    for (i = v.begin(); i != v.end(); i++)
    {
        cout << *i << ' ';
    }
}

int main()
{
    vector <double> v1;
    vector <double> v2;
    int n;
    int counter = 0;
    double x;

    cout << "Size 1: ", cin >> n;
    while (counter < n)
    {
        cout << "Enter data: ";
        cin >> x;
        v1.push_back(x);
        counter++;
    }

    counter = 0;
    cout << "Size 2: ", cin >> n;
    while (counter < n)
    {
        cout << "Enter data: ";
        cin >> x;
        v2.push_back(x);
        counter++;
    }

    vector <double> v(v1.size()+v2.size());
    concat(v1, v2, v);

    return EXIT_SUCCESS;
}