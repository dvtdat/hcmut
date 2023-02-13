#include <iostream>

using namespace std;

/*
The sum of a diagonal is the sum of all elements on it. 
Find the absolute value of the difference between the sums of two diagonal 
containing the cell which is represented by x and y of the given array.
*/

int diagonalDiff(int arr[][1000], int row, int col, int x, int y) 
{
    int diag1 = 0, diag2 = 0;

    for (int k = -min(x, y); k <= min(row - x, col - y) - 1; ++k) diag1 += arr[x + k][y + k];
    for (int k = -min(row - x - 1, y); k <= min(x, col - y - 1); ++k) diag2 += arr[x - k][y + k];

    //cout << diag1 << ' ' << diag2 << '\n';

    return (abs(diag1 - diag2));
}

int main()
{
    int arr[][1000] = {{55,85,47,58},{31,4,60,67},{94,69,71,73},{51,62,64,90}};
    cout << diagonalDiff(arr,4,4,3,3);
}