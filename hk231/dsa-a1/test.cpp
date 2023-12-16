#include <iostream>
#include <vector>

using namespace std;

int moves = 0;

void inssort2(vector<pair<int, int>>& A, int n, int incr) {
    for (int i = incr; i < n; i += incr) {
        for (int j = i; (j >= incr) && A[j].first > A[j - 1].first; j -= incr) {
            swap(A[j], A[j - incr]);
            moves += 3;
        }
    }
}

void shellsort(vector<pair<int, int>>& A) {
    int n = A.size();
    for (int i = n / 2; i > 2; i /= 2) {
        for (int j = 0; j < i; j++) {
            inssort2(A, n - j, i);
        }
    }
    inssort2(A, n, 1);
}

int main() {
    vector<pair<int, int>> arr;
    arr.push_back({2, 'A'});
    arr.push_back({1, 'B'});
    arr.push_back({1, 'C'});
    arr.push_back({2, 'D'});
    arr.push_back({5, 'E'});
    shellsort(arr);

    cout << "Sorted Array: ";
    for (pair<int, int> num : arr) {
        cout << (char)num.second << " ";
    }
    cout << '\n';

    cout << "Number of moves: " << moves << '\n';

    return 0;
}
