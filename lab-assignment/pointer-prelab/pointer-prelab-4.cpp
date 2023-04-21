#include <iostream>

using namespace std;

void deleteMatrix(int**& matrix, int r)
{
    for (int i = 0; i < r; ++i)
    {
       matrix[i] = NULL;
    }
    matrix = NULL;
}

int main()
{
    int** arr = new int*[3];
    arr[0] = new int[2]; arr[0][0] = 1; arr[0][1] = 2;
    arr[1] = new int[2]; arr[1][0] = 1; arr[1][1] = 2;
    arr[2] = new int[2]; arr[2][0] = 1; arr[2][1] = 2;

    deleteMatrix(arr, 3);
}