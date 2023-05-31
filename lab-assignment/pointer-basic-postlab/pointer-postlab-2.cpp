#include <iostream>

using namespace std;

void reverse(int *ptr, int n)
{
    for (int i = 0; i < n / 2; ++i)
    {
        int tmp = *(ptr + i);
        *(ptr + i) = *(ptr + n - i - 1);
        *(ptr + n - i - 1) = tmp;
    }
}

int main()
{
    int n; cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) cin >> arr[i];
    reverse(arr, n);

    for (int i = 0; i < n; ++i) cout << arr[i] << ' ';
}