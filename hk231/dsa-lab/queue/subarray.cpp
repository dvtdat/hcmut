#include <iostream>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

int sumOfMaxSubarray(vector<int>& nums, int k) {
    int total = 0;
    int n = (int)nums.size();
    deque<int> q;

    for (int i = 0; i < n; ++i) {
        while (q.size() && q.front() < i - k + 1) q.pop_front();
        while (q.size() && nums[q.back()] <= nums[i]) q.pop_back();
        q.push_back(i);

        if (i >= k - 1) total += nums[q.front()];
    }

    return total;
}

int main() {
    vector<int> nums {1, 2, 4, 3, 6};
    int k = 3;
    cout << sumOfMaxSubarray(nums, k);
}