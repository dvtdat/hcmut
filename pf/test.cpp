#include <iostream>

using namespace std;

int main()
{
    int** a = new int*[30]{};
    cout << '\n';

    int* b = new int;
    int* c = new int;
    int* d = new int;
    a[0] = b;
    a[1] = c;
    a[2] = d;
    for (int i = 0; i < 30; ++i) cout << a[i] << ' ';
    cout << '\n';
}