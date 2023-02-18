#include <iostream>

using namespace std;

int primeColumns(int arr[][1000], int row, int col) 
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

        cnt += flag;
    }

    return cnt;
}

int main()
{
    int arr[][1000] = {{34,-15,11,-70,-23,24},{-39,-90,63,-45,-52,48},{-42,92,55,92,82,81}};
    cout << primeColumns(arr,3,6);
}