#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void enlarge (vector <double> & v)
{
    vector <double> ::iterator i;
    for (i = v.begin()+1; i != v.end(); i++)
    {
        i = v.insert(i, (*i + *(i - 1))/2);
        i++;
    }

    cout << endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
}

int main()
{
    vector <double> v;
    int n;
    int counter = 0;
    double x;

    cout << "Size: ", cin >> n;
    while (cout << "Enter data: ", counter < n)
    {
        cin >> x;
        v.push_back(x);
        counter++;
    }

    enlarge(v);

    return EXIT_SUCCESS;
}