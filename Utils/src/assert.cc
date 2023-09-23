#include <functional>
#include <iostream>
#include <iomanip>
#include "../utils.h"

static int i = 1;


int utils::assert(std::function<int()> predicate) {
   std::cout << "Case" << " " << i++ << std::endl;
   int stat;
   try {
    stat = predicate();
   } catch (std::exception) {
    std::cout << "Caught an exception" << std::endl;
    return 1;
   }
   std::cout << std::endl;
   return stat;
}

int utils::runtest(std::string label, std::vector<std::function<int()>> tests) {
    i = 1;
    std::cout << "TEST" << " " << label << std::endl;
    std::vector<int> results;
    int i = 0;
    for (std::function<int()> predicate : tests) {
        int stat = assert(predicate);
        std::cout << (stat == 0 ? "SUCCESS" : "FAILED") << std::endl;
        results.push_back(stat);
    }
    struct {
        int c_success = 0;
        int c_failures = 0;
    } stats;
    for (int stat : results) {
        if (stat == 0) stats.c_success++;
        else stats.c_failures++;
    }
    std::cout << "RESULTS" << std::endl;
    std::cout << std::setw(10) << stats.c_success  << " " << "success cases" << std::endl;
    std::cout << std::setw(10) << stats.c_failures << " " << "failure cases" << std::endl;
    return 0;
}