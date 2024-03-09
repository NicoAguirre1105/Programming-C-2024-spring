#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void del (vector <double> & v)
{
    vector <double> v_new;
    for(int i = 1; i < v.size(); i+=2){
        v_new.push_back(v[i]);
    }
    v = v_new;

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

    del(v);

    return EXIT_SUCCESS;
}