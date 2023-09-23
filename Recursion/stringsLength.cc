#include <iostream>

using namespace std;

int strLen(char* str)     
{ 
    if (*str == '\0') return 0;
    int a = strLen(str+1);
    return a+1;
}

#include <functional>

int assert(std::function<void()> callback) {
   static int i = 0;
   std::cout << "Case" << " " << ++i << std::endl;
   callback();
   std::cout << std::endl;
   return 0;
}

int main() {
    assert([]() {
        char str[] = "Truong DH Bach Khoa";
        cout << strLen(str);
    });
    assert([]() {
        char str[] = "";
        cout << strLen(str);
    });
    return 0;
}