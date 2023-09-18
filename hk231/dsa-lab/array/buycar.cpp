#include <iostream>

int buyCar(int* nums, int length, int k) {
	for (int i = 0; i < length - 1; ++i) {
		for (int j = i + 1; j < length; ++j) {
			if (nums[i] > nums[j]) std::swap(nums[i], nums[j]);
		}
	}

	int total = 0;
	int cnt = 0;
	for (int i = 0; i < length && total + nums[i] <= k; ++i) {
		total += nums[i];
		cnt++;
	}

	return cnt;
}

int main() {
	int nums[] = {90, 30, 40, 90, 20};
	int length = sizeof(nums) / sizeof(nums[0]);
	std::cout << buyCar(nums, length, 90) << "\n";
}