#include <bits/stdc++.h>

using namespace std;

int recursiveSearch(int &n, int m, int arr[], int index)
{
    if (index >= n) return -1;
    if (arr[index] == m)
    {
        for (int i = index + 1; i < n; ++i) arr[i - 1] = arr[i];
        --n;
        return index;
    }

    return recursiveSearch(n, m, arr, index + 1);
}

int main()
{
    int n, k; cin >> n >> k;
    int arr[1000];
    for (int i = 0; i < n; ++i) cin >> arr[i];

    cout << recursiveSearch(n, k, arr, 0) << '\n';
    for (int i = 0; i < n; ++i) cout << arr[i] << ' ';

}