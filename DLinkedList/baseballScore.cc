#include <string>

#include <iostream>
#include "../Utils/utils.h"

using namespace std;

bool isNumber(char ch) {
    int offset = ch - '0';
    if (offset >= 0 && offset <= 9) return true;
    return false;
}

int baseballScore(string ops){
/*TODO*/
    std::vector<int> scores;
    for (char op : ops) {
        if (op == 'C') {
            scores.pop_back();
        } else if (op == 'D') {
            scores.push_back(scores.back()*2);
        } else if (op == '+') {
            int first = *(scores.end() - 1).base();
            int second = *(scores.end() - 2).base();
            scores.push_back(first + second);
        } else if (isNumber(op)) {
            scores.push_back(op - '0');
        }
    }

    int sum = 0;
    for (int val : scores) {
        sum += val;
    }
    return sum;
}

int main() {
    cout << baseballScore("524CD9++");
    return 0;
}