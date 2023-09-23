#include <vector>
#include <iostream>
#include "../Utils/utils.h"

using namespace std;

vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations) {
    // STUDENT ANSWER
    for (vector<int> op : operations) {
        unsigned int L = op[0];
        unsigned int R = op[1];
        unsigned int X = op[2];

        if (L < 0) throw std::exception();
        if (R >= nums.size()) throw std::exception();

        for (unsigned int i = L; i <= R; i++) {
            nums[i] += X;
        }
    }
    return nums;
}

void printVector(vector<int> list) {
    string str("");
    str += "[";
    for (size_t i = 0; i < list.size(); i++) {
        if (i == 0) str += to_string(list[i]);
        else str += ", " + to_string(list[i]);
    }
    str += "]";
    std::cout << str << std::endl;
}

int main() {
    utils::runtest("updateArrayPerRange", {
        []() {
            vector<int> nums {13, 0, 6, 9, 14, 16};
            vector<vector<int>> operations {{5, 5, 16}, {3, 4, 0}, {0, 2, 8}};
            printVector(updateArrayPerRange(nums, operations));
            return 0;
        },
        []() {
            vector<int> nums {19, 4, 3, 2, 16, 3, 17, 8, 18, 12};
            vector<vector<int>> operations {{0, 3, 4}, {2, 5, 12}, {3, 6, 6}, {5, 8, 5}, {8, 9, 8}, {0, 5, 9}, {1, 7, 8}, {1, 1, 3}, {5, 5, 18}};
            printVector(updateArrayPerRange(nums, operations));
            return 0;
        },
    });
    return 0;
}