#include <iostream>

using namespace std;

int diagonalProduct(int arr[][1000], int row, int col)
{
    int res = 1;
    for (int i = 0; i < row; ++i) res *= arr[i][i];
    return res;
}

int main()
{
    int arr[][1000] = {{-11,44,18,33},{-34,-9,-42,-42},{47,-26,4,-8},{-35,11,-34,-19}};
    cout << diagonalProduct(arr,4,4);
}