#include <iostream>

using namespace std;

int* flatten(int** matrix, int r, int c)
{
    int* tmp = new int[r * c];
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j) tmp[i * c + j] = matrix[i][j];
    }
    return tmp;
}

int main()
{
    int n = 2, m = 3;
    int** arr = new int*[n];
    arr[0] = new int[m]; arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3;
    arr[1] = new int[m]; arr[1][0] = 4; arr[1][1] = 5; arr[1][2] = 6;

    int* newArr = flatten(arr, n, m);

    for (int i = 0; i < n * m; ++i)
    {
        cout << newArr[i] << ' ';
    }
}