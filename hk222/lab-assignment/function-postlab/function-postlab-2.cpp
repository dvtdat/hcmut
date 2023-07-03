#include <iostream>
#include <string>

using namespace std;

int convertToBaseM(int n, int m)
{
    int res = 0;
    int l = n;
    int pow = 1;
    while (l != 0)
    {
        res = res + (l % m) * pow;
        pow = pow * 10;
        l = l / m;
    }
    return res;
}

int main()
{
    int n, m; cin >> n >> m;
    cout << convertToBaseM(n, m) << '\n';
}