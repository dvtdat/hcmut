#include <iostream>

using namespace std;

bool completeNum(int N)
{
    int tmp = 0;
    for (int i = 1; i <= N / 2; ++i) tmp += (N % i == 0 ? i : 0);
    return (tmp == N ? true : false);
}

int main()
{
    int n; cin >> n;
    if (completeNum(n)) cout << "true"; 
    else cout << "false";
}