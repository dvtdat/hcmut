#include <iostream>
#include <string>

using namespace std;

/*Coins Change - a classic one*/

int count(int k, int i)
{
    if (k == 0) return 1;           // BASE CASE
    if (k < 0 || i <= 0) return 0;  
    return count(k - i * i, i - 1) + count(k, i - 1);
}

int countWaySumOfSquare(int k)
{
    return count(k, 100);
}

int main()
{
    int n;
    while (cin >> n && n != 0) cout << countWaySumOfSquare(n) << '\n';
}