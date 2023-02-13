#include <iostream>

using namespace std;

/*
A row of the given array is called as HN1 if on this row, each element's value is not higher than all elements after it. 
Find the number of HN1 rows of the given array.
*/

int ascendingRows(int arr[][1000], int row, int col) 
{
    int cnt = 0;
    for (int i = 0; i < row; ++i)
    {
        bool flag = true;
        for (int j = 1; j < col; ++j) 
        {
            if (arr[i][j] < arr[i][j - 1]) flag = false;
        }
        if (flag) cnt++;
    }

    return cnt;
}

int main()
{
    int arr[][1000] = {{-28,-8,-60,18},{-100,44,-1,24},{-94,92,-70,75}};
    cout << ascendingRows(arr,3,4);
}