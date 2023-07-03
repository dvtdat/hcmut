#include <iostream>

using namespace std;

int** transposeMatrix(int** matrix, int r, int c)
{
    if (r == 0 || c == 0) return NULL;
    int** tmp = new int*[c];
    for (int i = 0; i < c; ++i) tmp[i] = new int[r];

    for (int i = 0; i < c; ++i)
    {
        for (int j = 0; j < r; ++j)
        {
            tmp[i][j] = matrix[j][i];
        }
    }

    return tmp;
}

int main()
{
    int n = 2, m = 3;
    int** arr = new int*[n];
    arr[0] = new int[m]; arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3;
    arr[1] = new int[m]; arr[1][0] = 4; arr[1][1] = 5; arr[1][2] = 6;

    int** arr2 = transposeMatrix(arr, n, m);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << arr2[i][j] << ' ';
        }
        cout << '\n';
    }
}