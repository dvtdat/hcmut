#include <iostream>
#include <string>

using namespace std;

bool deleteRow(int**& matrix, int r, int c, int row)
{
    if (row >= r) return false;
    if (row == r - 1 && r == 1)
    {
        delete[] matrix[0];
        delete[] matrix;
        matrix = nullptr;
        return true;
    }

    int** newMat = new int*[r - 1];
    for (int i = 0; i < r - 1; ++i) newMat[i] = new int[c];

    bool flag = false;
    for (int i = 0; i < r; ++i)
    {
        if (i == row)
        {
            flag = true;
            continue;
        }
        for (int j = 0; j < c; ++j)
        {
            newMat[i - flag][j] = matrix[i][j]; 
        }
    }

    for (int i = 0; i < r; ++i) delete[] matrix[i];
    delete[] matrix;

    matrix = newMat;
    return true;
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
    bool flag = deleteRow(mat, n, m, idx);

    if (!flag)
    {
        cout << "There is no way..."; return 0;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << mat[i][j] << ' ';
        }
        cout << '\n';
    }
}