#include <iostream>

using namespace std;

// Hiện thực hàm:
// int specialCells(int arr[][1000], int row, int col);
// Trong đó; arr, row và col lần lượt là mảng 2 chiều, số hàng và số cột của mảng. Một ô trong mảng được gọi là HN3 nếu tổng tất cả các phần tử
// trong hàng chứa ô đó và tổng tất cả các phần tử trong cột chứa ô đó đều là số nguyên tố. Tìm số ô HN3 trong mảng.

bool isColPrime[1000];
bool isRowPrime[1000];

void primeColumns(int arr[][1000], int row, int col) 
{
    int cnt = 0;
    for (int i = 0; i < col; ++i)
    {
        int sum = 0;
        for (int j = 0; j < row; ++j) sum += arr[j][i];
        
        if (sum <= 0) continue;

        bool flag = true;
        for (int k = 2; k <= sum / 2 + 1 && sum > 0; ++k)
            if (sum % k == 0) flag = false;

        isColPrime[i] = true;
    }
}

void primeRows(int arr[][1000], int row, int col) 
{
    int cnt = 0;
    for (int i = 0; i < row; ++i)
    {
        int sum = 0;
        for (int j = 0; j < col; ++j) sum += arr[i][j];
        
        if (sum <= 0) continue;

        bool flag = true;
        for (int k = 2; k <= sum / 2 + 1 && sum > 0; ++k)
            if (sum % k == 0) flag = false;

        isRowPrime[i] = true;
    }
}

int specialCells(int arr[][1000], int row, int col)
{
    for (int i = 0; i < row; ++i) isRowPrime[i] = false;
    for (int i = 0; i < col; ++i) isColPrime[i] = false;
    primeColumns(arr, row, col);
    primeRows(arr, row, col);

    int cnt = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (isRowPrime[i] && isColPrime[j]) cnt++;
        }
    }
    return cnt;
}

int main()
{
    int arr[][1000] = {{-28,-8,-60,18},{-100,44,-1,24},{-94,92,-70,75}};
    cout << specialCells(arr, 3, 6) << '\n';
}