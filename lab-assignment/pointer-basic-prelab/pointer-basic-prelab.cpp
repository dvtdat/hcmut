#include <iostream>

using namespace std;

int getValueAtIndex(int *ptr, int k)
{
    return ptr[k];
}

void swap(int *ptr1, int *ptr2)
{
    int tmp = *ptr2;
    *ptr2 = *ptr1;
    *ptr1 = tmp;
}

int main()
{
    // int arr[] = {1, 2, 3, 4, 5};
    // int k = 3;
    // cout << getValueAtIndex(arr, k);

    int a = 5;
    int b = 6;
    swap(&a, &b);
    cout << a << ' ' << b;
}