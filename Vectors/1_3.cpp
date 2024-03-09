#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

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
    
    double array[n];

    copy(v.begin(), v.end(), array);

    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << array[i] << " ";
    }

    return EXIT_SUCCESS;
}