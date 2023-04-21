#include <iostream>

using namespace std;

void printPattern2(int cnt, int n, int flag)
{
    if (cnt == -1) return;
    if (n <= 0) flag = -flag;
    cout << n << ' ';
    printPattern2(cnt + flag, n - flag * 5, flag);
}

void printPattern(int n)
{
    printPattern2(0, n, 1);
}   

int main()
{
    printPattern(16);
}