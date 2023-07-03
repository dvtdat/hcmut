#include <iostream>

using namespace std;

void insertRow(int **& ptr, int r, int c, int* rowArr, int row)
{
    for (int i = r; i > row; --i)
    {
        ptr[i] = ptr[i - 1];
    }
    ptr[row] = rowArr;
}

int main()
{
    int r, c; cin >> r >> c;
    int matrix[r][c];
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cin >> matrix[i][j];
        }
    }
}