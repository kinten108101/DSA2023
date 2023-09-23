#include <vector>
#include <iostream>
#include "../Utils/utils.h"

int equalSumIndex(std::vector<int>& nums) {
    unsigned int size = nums.size();
    if (size == 1) return 0;
    if (size < 3) return -1;
    int lhs = nums[0];
    int rhs = 0;
    for (unsigned int i = 2; i <= size - 1; i++) {
        rhs += nums[i];
    }
    if (lhs == rhs) return 1;

    for (unsigned int i = 0; i <= size - 3; i++) {
        int a = nums[1+i];
        int b = nums[1+i+1];
        lhs += a;
        rhs -= b;
        if (lhs == rhs) return 1+i+1;
    }
    return -1;
}

int main() {
    utils::runtest("Equal Sum Index", {
        []() {
            std::vector<int> nums {3, 5, 2, 7, 6, 4};
            int result = equalSumIndex(nums);
            std::cout << result;
            if (result != 3) return 1;
            return 0;
        },
        []() {
            std::vector<int> nums {3};
            int result = equalSumIndex(nums);
            std::cout << result;
            if (result != 0) return 1;
            return 0;
        },
    });
    return 0;
}