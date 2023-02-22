#include <bits/stdc++.h>

using namespace std;

const int inf = INT_MAX;

int main()
{
    int arr[4] = {1, 2, 3, 4};
    int n = 4; 

    int mx = -inf, mxIndex = -1, sMx = -inf, sMxIndex = -1;
    for (int i = 0; i < n; ++i)
    {
        if (mx < arr[i])
        {
            sMx = mx;
            sMxIndex = mxIndex;

            mx = arr[i];
            mxIndex = i;
        }
    }

    if (sMxIndex == -1) cout << "Cant found\n";
    else cout << sMxIndex << ' ' << sMx << '\n';
}