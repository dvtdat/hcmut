#include <iostream>
#include <string>

using namespace std;

int** insertCol(int**& matrix, int r, int c, int* colArr, int col)
{
    int** newMat = new int*[r];
    for (int i = 0; i < r; ++i) newMat[i] = new int[c + 1];

    for (int i = 0; i < r; ++i)
    {
        bool flag = false;
        for (int j = 0; j < c + 1; ++j)
        {
            if (j == col) newMat[i][j] = colArr[i], flag = true;
            else newMat[i][j] = matrix[i][j + flag];
        }
    }

    for (int i = 0; i < r; ++i) delete[] matrix[i];
    delete[] matrix;

    return newMat;
}

int main()
{
    int n, m; cin >> n >> m;
    int** mat = new int*[n];
    for (int i = 0; i < n; ++i)
    {
        mat[i] = new int[m];
        for (int j = 0; j < m; ++j) cin >> mat[i][j];
    }

    int idx; cin >> idx;
    int* colMat = new int[n];
    for (int i = 0; i < n; ++i) cin >> colMat[i];

    int** newMat = insertCol(mat, n, m, colMat, idx);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m + 1; ++j) cout << newMat[i][j] << ' ';
        cout << '\n';
    }
}