#include <iostream>

using namespace std;

int findMax(int* ptr, int n)
{
    int res = -1e9;
    for (int i = 0; i < n; ++i)
    {
        res = max(res, *(ptr + i));
    }
    return res;
}

int main()
{
    int n; cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) cin >> arr[i];
    cout << findMax(arr, n);
}