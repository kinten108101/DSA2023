#include <iostream>
#include <string>
#include "../Utils/utils.h"

using namespace std;

string _reverseSentence(string &s, unsigned int idx, int wordidx) {
    if (idx >= s.length()) return "";
    string word = s.substr(idx, s.find(' ', idx + 1) - idx);
    string buffer = _reverseSentence(s, idx+=word.length() + 1, ++wordidx);
    if (idx >= s.length()) {
        return buffer += word;
    }
    return buffer += " " + word;
}

string reverseSentence(string s) {
    return _reverseSentence(s, 0, 0);
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
    utils::runtest("Recursion", {
        []() {
            string str(reverseSentence("the replacing used son Odorless is Substances fluids for He"));
            if (str != "He for fluids Substances is Odorless son used replacing the") return 1;
            return 0;
        },
        []() {
            string str(reverseSentence("data structure and algorithm is scary"));
            if (str != "scary is algorithm and structure data") return 1;
            return 0;
        },
    });
    return 0;
}   
