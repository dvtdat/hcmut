#include <iostream>

using namespace std;

int sum1(int arr[], int size)
{

}

int sum2(int *arr, int size) // same meaning as the sum1
{
    if (size == 1) return arr[0];

    int left[10010], right[10010];
    int mid = size / 2;
    for (int i = 0; i < mid; ++i) left[i] = arr[i];
    for (int i = mid; i < size; ++i) right[i - mid] = arr[i];

    return (sum2(left, mid) + sum2(right, size - mid));
}

int sum3(int a, int b) 
{
    /*
    Truyền tham trị
    Tạo ra một vùng nhớ mới (ở đây là 2 biến a và b mới)
    */
}

int sum4(int &a, int &b) 
{
    /*
    Truyền tham khảo
    Dùng vùng nhớ cũ của a và b
    */
}

void sum5(int *arr, int size, int &sum)
{

}

int main()
{
    // int arr[] = {1, 2, 3, 4, 5};
    // cout << sum2(arr, 5);

    int val = 100;
    int* ptr = &val;

    cout << val << ' ' << &val << ' ' << ptr << ' ' << *ptr << ' ' << ptr << '\n';
    cout << *&val << ' ' << *&ptr << '\n';
}