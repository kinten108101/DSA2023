#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../Utils/utils.h"

int buyCar(int* nums, int length, int k) {
	std::vector<int> v(nums, nums + length);
	std::sort(v.begin(), v.end());
	int bought = 0;
	int items = 0;
	for (int val : v) {
		if (bought + val > k) break;
		items++;
		bought += val;
	}
	return items;
}

int main() {
	utils::runtest("Buy Cars", {
		[]() {
			int nums[] = {90,30,40,900,20};
			int length = sizeof(nums)/sizeof(nums[0]);
			int result = buyCar(nums, length, 90);
			std::cout << result << "\n";
			if (result != 3) return 1;
			return 0;
		},
		[]() {
			int nums[] = {90,30,40,90,20,70,150,300};
			int length = sizeof(nums)/sizeof(nums[0]);
			int result = buyCar(nums, length, 200);
			std::cout << result << "\n";
			if (result != 4) return 1;
			return 0;
		},
		[]() {
			int nums[] = {80,120,150,30,500,260,170,200,50};
			int length = sizeof(nums)/sizeof(nums[0]);
			int result = buyCar(nums, length, 500);
			std::cout << result << "\n";
			if (result != 5) return 1;
			return 0;
		},
		[]() {
			int nums[] = {50,90,180,300,52,46,285,78,42,966,135,545,858,47,124};
			int length = sizeof(nums)/sizeof(nums[0]);
			int result = buyCar(nums, length, 1000);
			std::cout << result << "\n";
			if (result != 10) return 1;
			return 0;
		},
		[]() {
			int nums[] = {50,90,180,300,52,46,285,78,42,966,135,545,858,47,124};
			int length = sizeof(nums)/sizeof(nums[0]);
			int result = buyCar(nums, length, 10);
			std::cout << result << "\n";
			if (result != 0) return 1;
			return 0;
		}
	});
	return 0;
}