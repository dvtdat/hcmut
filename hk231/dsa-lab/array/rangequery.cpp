#include <iostream>
#include <vector>

using namespace std;

vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations) {
    int n = (int)nums.size();

    vector<int> pre(n, 0);

    for (int i = 0; i < (int)operations.size(); ++i) {
        pre[operations[i][0]] += operations[i][2]; 
        pre[operations[i][1] + 1] -= operations[i][2]; 
    }

    for (int i = 1; i < n; ++i) pre[i] += pre[i - 1];
    for (int i = 0; i < n; ++i) pre[i] += nums[i];

    return pre;
}

int main() {
    vector<int> nums {13, 0, 6, 9, 14, 16};
    vector<vector<int>> operations {{5, 5, 16}, {3, 4, 0}, {0, 2, 8}};
    vector<int> ans = updateArrayPerRange(nums, operations);

    for (auto i : ans) cout << i << '\n';
}