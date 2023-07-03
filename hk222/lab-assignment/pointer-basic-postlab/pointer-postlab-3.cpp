#include <iostream>

using namespace std;

bool isSymmetry(int *head, int *tail)
{
    while (head != tail && head - 1 != tail)
    {
        if (*head != *tail) return false;
        head = head + 1;
        tail = tail - 1;
    }
    return true;
}

int main()
{
    int n; cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) cin >> arr[i];
    cout << isSymmetry(arr, arr + n - 1);
}