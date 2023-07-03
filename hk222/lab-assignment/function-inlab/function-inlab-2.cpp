#include <iostream>

using namespace std;

bool isPrime(int n)
{
    if (n == 1) return false;
    for (int i = 2; i <= n / 2; ++i)
        if (n % i == 0) return false;

    return true;
}

bool isSpecialNumber(int n)
{
    int sum = 0;
    int m = n;

    while (m > 0)
    {
        sum += m % 10;
        m /= 10;
    }

    return ((isPrime(sum) && isPrime(n)) ? true : false);
}

int main()
{
    int n;

    cin >> n;
    cout << isSpecialNumber(n);
}