#include "queue.h"
#include <iostream>
#include "../Utils/utils.h"

int main() {
	utils::runtest("Queue Basic", {
		[]() {
			Queue<int> queue;
			queue.push(7);
			queue.push(5);
			queue.push(12);
			queue.pop();
			auto str = queue.toString();
			std::cout << str << std::endl;
			if (str != "[5,12]") return 1;
			return 0;
		},
		[]() {

			Queue<int> queue;

		    int item[] = { 3, 1, 4, 5, 2, 8, 10, 12 };
		    //index:  0  1  2  3  4  5  6   7
		    for (int idx = 0; idx < 8; idx++)
		    	queue.push(item[idx]);

		    queue.clear();
		    if (queue.empty() != true) return 1;
		    if (queue.size() != 0) return 1;
			return 0;
		},
	});
	return 0;
}