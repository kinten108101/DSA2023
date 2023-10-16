#include <stack>
#include <string>
#include <sstream>

#include <iostream>
#include "../Utils/utils.h"

int evaluatePostfix(std::string expr){
    /*TODO*/
    std::stringstream ss(expr);
    std::string buffer;
    std::stack<int> vals;
    while (ss >> buffer) {
        int number;
        try {
            number = std::stoi(buffer);
            vals.push(number);
        } catch (std::exception) {
            char op = buffer[0];
            if (op == '+') {
                int b = vals.top();
                vals.pop();
                int a = vals.top();
                vals.pop();
                vals.push(a + b);
            } else if (op == '-') {
                int b = vals.top();
                vals.pop();
                int a = vals.top();
                vals.pop();
                vals.push(a - b);
            } else if (op == '*') {
                int b = vals.top();
                vals.pop();
                int a = vals.top();
                vals.pop();
                vals.push(a * b);
            } else if (op == '/') {
                int b = vals.top();
                vals.pop();
                int a = vals.top();
                vals.pop();
                vals.push(a / b);
            }
        }
    }
    return vals.top();
}

int main() {
    utils::runtest("postfix", {
        []() {
            std::string expr("1 2 +");
            int val = evaluatePostfix(expr);
            std::cout << val << std::endl;
            if (val != 3) return 1;
            return 0;
        },
        []() {
            std::string expr("2 3 1 * + 9 -");
            int val = evaluatePostfix(expr);
            std::cout << val << std::endl;
            if (val != -4) return 1;
            return 0;
        },
        []() {
            std::string expr("100 200 + 2 / 5 * 7 +");
            int val = evaluatePostfix(expr);
            std::cout << val << std::endl;
            if (val != 757) return 1;
            return 0;
        },
    });
    return 0;
}