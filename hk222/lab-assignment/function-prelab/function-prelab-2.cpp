#include <iostream>

using namespace std;

int findMax(int *vals, int numEls) 
{
    int mx = -1000000000;
    for (int i = 0; i < numEls; ++i) 
        mx = max(mx, vals[i]);

    return mx;
}

int main()
{
    int arr[100];

    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr[i];

    int mx = findMax(arr, n);

    cout << mx;
}