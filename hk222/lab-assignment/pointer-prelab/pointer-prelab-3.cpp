#include <iostream>

using namespace std;

int** deepCopy(int** matrix, int r, int c) {
    if (r <= 0 || c <= 0) return nullptr;
    
    int** tmp = new int*[r];
    for (int i = 0; i < r; ++i)
    {
        tmp[i] = new int[c];
    }

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            tmp[i][j] = matrix[i][j];
        }
    }
    return tmp;
}

int main()
{
    int** m = new int*[2];
    m[0] = new int[2]; m[0][0] = 1; m[0][1] = 2;
    m[1] = new int[2]; m[1][0] = 1; m[1][1] = 3;
    int** n = deepCopy(m, 2, 2);
    cout << n[0][0] << ' ' << n[0][1] << '\n' << n[1][0] << ' ' << n[1][1];
}