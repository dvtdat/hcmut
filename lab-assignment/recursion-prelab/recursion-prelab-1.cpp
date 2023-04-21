#include<iostream>
#include<string>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>

using namespace std;

int gcdIteration(int p, int q)
{
    for (int i = min(p, q); i > 0; --i)
    {
        if (p % i == 0 && q % i == 0) return i;
    }
}

int gcdRecursion(int p, int q)
{
    if (p == 0) return q;
    if (q == 0) return p;
    if (p == q) return p;
    if (p > q) return gcdRecursion(p - q, q);
    return gcdRecursion(p, q - p);
}

int main()
{
    int p, q;
    cin >> p >> q;
    cout << gcdRecursion(p, q) << " " << gcdIteration(p, q);
    return 0;
}