#include <iostream>

using namespace std;

void addElement(int*& arr, int n, int val, int idx)
{
    int* tmp = new int[n + 1];
    for (int i = 0; i < idx; ++i) tmp[i] = arr[i];
    for (int i = idx + 1; i < n + 1; ++i) tmp[i] = arr[i - 1];
    tmp[idx] = val;

    delete[] arr;
    arr = tmp;

    // delete[] tmp;
    // delete[] tmp make core dumped
}

int main()
{
    int n = 2;
    int* arr = new int[2];
    arr[0] = 2;
    arr[1] = 3;
    
    addElement(arr, n, 1, 1);
    for (int i = 0; i < n + 1; ++i) cout << arr[i] << ' ';
}