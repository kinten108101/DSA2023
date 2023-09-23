#include <vector>
#include <iostream>
#include "../Utils/utils.h"

bool consecutiveOnes(std::vector<int>& nums) {
    unsigned int size = nums.size();
    if (size == 0) return true;
    // STUDENT ANSWER
    int inflections = 0;
    bool found_a_one = false;
    for (int i = 0; i < size; i++) {
        if (inflections > 2) break;
        if (nums[i] != 1) {
            if (found_a_one) {
                found_a_one = false;
                inflections++;
                continue;
            }
            else continue;
        }
        if (!found_a_one) {
            found_a_one = true;
            inflections++;    
        }
    }

    if (inflections > 2) return false;
    return true;
}

int main() {
    utils::runtest("Consecutive Ones", {
        []() {
            std::vector<int> nums {0, 1, 1, 1, 9, 8};
            std::cout << consecutiveOnes(nums);
            return 0;
        },
    });
    return 0;
}