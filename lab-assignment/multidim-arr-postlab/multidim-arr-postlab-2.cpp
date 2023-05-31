#include <iostream>

using namespace std;

// Hiện thực hàm:
// int subMatrix(int arr[][1000], int row, int col);
// Trong đó; arr, row và col lần lượt là mảng 2 chiều, số hàng và số cột của mảng. Một mảng con kích thước 2x2 thuộc mảng đã cho được gọi là HN4
// nếu tổng tất cả các phần tử trong nó là một số lẻ. Tìm số mảng con HN4 trong mảng đã cho.

int subMatrix(int arr[][1000], int row, int col)
{
    int cnt = 0;
    for (int i = 0; i < row - 1; ++i)
    {
        for (int j = 0; j < col - 1; ++j)
        {
            int sum = arr[i][j] + arr[i][j + 1] + arr[i + 1][j] + arr[i][j];
            if (sum % 2) cnt++;
        }
    }
    return cnt;
}

int main()
{
    int arr[][1000] = {{-28,-8,-60,18},{-100,44,-1,24},{-94,92,-70,75}};
    cout << subMatrix(arr, 3, 6) << '\n';
}