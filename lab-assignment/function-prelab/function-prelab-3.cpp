#include <iostream>

using namespace std;

void sum2(int * array, int numEls, int &result)
{
    result = 0;
    for (int i = 0; i < numEls; ++i) result += array[i];
}

int main()
{
    int arr[100];

    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr[i];

    int res = 0;
    sum2(arr, n, res);

    cout << res;
}