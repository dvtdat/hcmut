#include <iostream>

using namespace std;

void shallowCopy(int*& newArr, int*& arr)
{
    for (int i = 0; i < sizeof(arr); ++i)
    {
        newArr[i] = arr[i];
    }
}

int main()
{
    int* arr = new int[2];
    arr[0] = 2; arr[1] = 3;
    int* newArr = nullptr;

    shallowCopy(newArr, arr);
    cout << newArr[0] << ' ' << newArr[1];
    
    delete[] arr;
}