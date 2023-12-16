#include <functional>
#include <iostream>
#include <string>

long int midSquare(long int seed)
{
    std::string buf(std::to_string((seed * seed) / 100));
    if (buf.length() <= 4) return stoi(buf);
    return stoi(buf.substr(buf.length() - 4, 4));
}

long int moduloDivision(long int seed, long int mod)
{
    return seed % mod;
}

long int digitExtraction(long int seed, int* extractDigits,int size)
{
    std::string num;
    std::string sample(std::to_string(seed));
    for (int i = 0; i < size; i++) {
        num += sample[extractDigits[i]];
    }
    return stoi(num);
}

void test_hash_in_c(std::string sample) {
	std::cout << "> hash-in-c" << std::endl;
	std::cout << std::hash<std::string>{}(sample) << std::endl;
}

void test_digit_extraction() {
	std::cout << "> digit-extraction" << std::endl;
	int a[]={1,2,5};
	std::cout << digitExtraction(122443,a,3) << std::endl;
}

void test_mid_square() {
	std::cout << "> mid-square" << std::endl;
	std::cout << midSquare(9452) << std::endl;
}

int main(int argc, char *argv[]) {
	if (argc >= 2) {
		std::string input(argv[1]);
		test_hash_in_c(input);
	}

	test_digit_extraction();
	test_mid_square();

	return 0;
}