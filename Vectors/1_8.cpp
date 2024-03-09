#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

bool subseq (vector <int> v1, vector <int> v2)
{
    bool is_subseq = true;
    vector <int> :: iterator i = v1.begin();

    for (int n : v2)
    {
        i = find(i, v1.end(), n);
        if(i == v1.end())
        {
            is_subseq = false;
            break;
        }
    }

    return is_subseq;
}

int main()
{
    vector <int> v1;
    vector <int> v2;
    int n;
    int counter = 0;
    int x;

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

    bool is_subseq = subseq(v1, v2);
    cout << is_subseq;

    return EXIT_SUCCESS;
}