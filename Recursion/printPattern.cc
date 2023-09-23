#include <iostream>
#include "../Utils/utils.h"

using namespace std;

void printPattern(int n) 
{
    cout << n;
    if (n > 0) cout << " ";
    if (n <= 0) {
        return;
    }
    printPattern(n-5);
    cout << " " << n;
}

#include <functional>

int assert(std::function<void()> callback) {
   static int i = 0;
   std::cout << "Case" << " " << ++i << std::endl;
   callback();
   std::cout << endl;
   return 0;
}

int main() {
    utils::runtest("printPattern", {
        []() {
            printPattern(14);
            return 0;
        },
        []() {
            printPattern(9);
            return 0;
        },
        []() {
            printPattern(20);
            return 0;
        },
    });
    return 0;
}
