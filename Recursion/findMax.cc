#include <iostream>
using namespace std;

int findMaxRecursion(int *arr, int current, int length) {
    if (current == length - 1) {
        return arr[current];
    }
    int next = findMaxRecursion(arr, current+1, length);
    if (arr[current] > next) return arr[current];
    else return next;
}

int findMax(int* arr, int length)
{
    return findMaxRecursion(arr, 0, length);
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
        int arr[] = {10, 5, 7, 9, 15, 6, 11, 8, 12, 2};
        cout << findMax(arr, 10);
    });
    assert([]() {
        int arr[] = {10, -1, -150, 200};
        cout << findMax(arr, 4);
    });
    assert([]() {
        int arr[] = {24,0,88,-59,-54,13,20,-11,22,-48,5,22,-40,-26,-97,88};
        cout << findMax(arr, 16);
    });
}


