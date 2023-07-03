#include <iostream>

using namespace std;

bool checkDuplicate(int* ar, int size)
{
    if (size <= 1) return true;

    int curr = 0;
    int left[10010], right[10010];
    int l = 0, r = 0;

    for (int next = 1; next < size; ++next)
    {
        if (ar[next] == ar[curr]) return false;
        if (ar[next] < ar[curr]) left[l++] = ar[next];
        if (ar[next] > ar[curr]) right[r++] = ar[next];
    }

    return (checkDuplicate(left, l) && checkDuplicate(right, r));
}

int main()
{
    int arr[] = {1, 2, 3, 3, 5};
    cout << checkDuplicate(arr, sizeof(arr) / sizeof(arr[0]));
}