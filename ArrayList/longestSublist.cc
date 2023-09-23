#include <vector>
#include <iostream>
#include <string>
#include "../Utils/utils.h"

int longestSublist(std::vector<std::string>& words) {
    unsigned int size = words.size();
    if (size == 0) return 0;
    // STUDENT ANSWER
    int max_streak = 1;
    int streak = 1;
    char sample = words[0][0];
    for (unsigned int i = 1; i < size; i++) {
        std::string &word = words[i];
        if (word[0] != sample) {
            if (streak > max_streak) max_streak = streak;
            streak = 1;
            sample = word[0];
            continue;
        }
        streak++;
    }
    if (streak > max_streak) max_streak = streak;
    return max_streak;
}

int main() {
    utils::runtest("Longest Sublist", {
        []() {
            std::vector<std::string> words {"faction", "fight", "and", "are", "attitude"};
            int result = longestSublist(words);
            std::cout << result;
            if (result != 3) return 1;
            return 0;
        },
    });
    return 0;
}