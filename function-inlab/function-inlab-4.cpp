#include <iostream>

using namespace std;

bool ok[1010];
bool checkElementsUniqueness(int* arr, int n) 
{
    for (int i = 0; i < 1001; ++i) ok[i] = false;

    for (int i = 0; i < n; ++i)
    {
        if (ok[arr[i]])
        {
            return false;
        }
        ok[arr[i]] = true;
    }

    return true;
}

int main()
{
    int n;
    cin >> n;
    int* arr = new int[n];
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << checkElementsUniqueness(arr, n);
    delete[] arr;
}