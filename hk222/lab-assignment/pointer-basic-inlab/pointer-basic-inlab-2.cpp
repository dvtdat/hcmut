#include <iostream>

using namespace std;

void add(int *ptr, int n, int k)
{
    *(ptr + n) = k;
}

int main()
{
    int arr[100] = {1, 2, 3, 4, 5};
    int n = 5;
    int k = 100;
    add(arr, n, k);
    cout << arr[n];
}