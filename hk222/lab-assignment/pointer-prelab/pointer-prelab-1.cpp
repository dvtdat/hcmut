#include <iostream>

using namespace std;

int* zeros(int n) {
    if (n <= 0) return nullptr;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) arr[i] = 0;
    return arr;
}

int main()
{
    int* arr = zeros(10);
    for (int i = 0; i < 10; ++i) cout << arr[i] << ' ';
}