#include <iostream>
#include <vector>
#include <string>

bool consecutiveOnes(std::vector<int>& nums) {
    int a = 0;
    int b = 0;

    for (int i = 0; i < (int)nums.size(); ++i) {
        if (nums[i] != 1) continue;

        if (i == 0) {
            a++; continue;
        }
        if (i == (int)nums.size() - 1) {
            b++; continue;
        }
        if (nums[i - 1] != 1) a++;
        if (nums[i + 1] != 1) b++;
    }
    // std::cout << a << ' ' << b << '\n';
    return (a <= 1 && b <= 1);
}

int equalSumIndex(std::vector<int>& nums) {
    int n = (int)nums.size();
    std::vector<int> p(n + 1);

    p[0] = 0;
    for (int i = 1; i <= n; ++i) p[i] = p[i - 1] + nums[i - 1];

    for (int i = 1; i <= n; ++i) {
        if (p[i - 1] == p[n] - p[i]) return i - 1;
    }

    return -1;
}

int longestSublist(std::vector<std::string>& words) {
    int length = (int)words.size();
    if (length == 0) return 0;
    
    int cur = 1;
    int mx = 1;
    for (int i = 1; i < length; ++i) {
        if (words[i][0] != words[i - 1][0]) {
            mx = std::max(mx, cur);
            cur = 1;
        } else cur++;
    }

    return std::max(mx, cur);
}

int main() {
    // std::vector<int> nums {1, 1, 1, 0, 0, 0, 0, 0, 0};
    // std::cout << consecutiveOnes(nums) << '\n';

    std::vector<std::string> words {};
    std::cout << longestSublist(words);
}