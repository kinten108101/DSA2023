#include <iostream>
using namespace std;

void printArray(int n)
{
    if (n == -1) {
        return;
    }
    printArray(n-1);
    if (n > 0) {
        cout << ", ";
    }
    cout << n;
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
    assert([]() {
        printArray(5);
    });
    assert([]() {
        printArray(17);
        cout << "a";
    });
    return 0;
}