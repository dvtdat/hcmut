#include <iostream>

using namespace std;

int calcSum(int *ptr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum += *(ptr + i);
    }

    return sum;
}

int main()
{
    int arr[] = {1, 2, 3, 5, 5};
    cout << calcSum(arr, sizeof(arr) / sizeof(arr[0]));
}