#include "stack.h"
#include <iostream>
#include "../Utils/utils.h"

int main() {
	utils::runtest("Stack Basic", {
		[]() {
			Stack<int> stack;
			stack.push(5);
			stack.push(12);
			auto str = stack.toString();
			std::cout << str << std::endl;
			if (str != "[5,12]") return 1;
			return 0;
		},
	});
	return 0;
}