#include <bits/stdc++.h>

using namespace std;

string rnd(double val)
{
    stringstream tmp;
    tmp << fixed << setprecision(4) << val;

    if (tmp.str()[tmp.str().length() - 1] != '0') return tmp.str();
    for (int i = tmp.str().length() - 1; i >= 0; --i)
    {
        if (tmp.str()[i] == '.') return tmp.str().substr(0, i);
        if (tmp.str()[i] != '0') return tmp.str().substr(0, i + 1);
    }
    return tmp.str();
}

int main()
{
    double v = 40.00100;
    cout << rnd(v);

}