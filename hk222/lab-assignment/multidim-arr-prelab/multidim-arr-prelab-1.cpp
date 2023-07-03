#include <iostream>

using namespace std;

int findMaxColumn(int arr[][1000], int row, int col) 
{
    int res = 0, mx = 0;
    for (int i = 0; i < col; ++i)
    {
        int tmp = 0;
        for (int j = 0; j < row; ++j) tmp += arr[j][i];

        if (tmp >= mx)
        {
            mx = tmp; res = i;
        }
    }
    
    return res;
}

int main()
{
    int arr[][1000] = {{-44,64,-6},{87,92,-19},{-92,53,-38},{-39,-92,21}};
    cout << findMaxColumn(arr, 4, 3);
}