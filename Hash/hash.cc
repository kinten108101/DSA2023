#include <functional>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
	if (argc != 2) return 1;
	std::string input(argv[1]);
	std::cout << std::hash<std::string>{}(input) << std::endl;
	return 0;
}