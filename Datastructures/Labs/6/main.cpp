#include <iostream>
#include <fstream>
#include <random>

#include "BaseTree.h"
#include "Colors.h"

int GenerateRandomInteger(const int& begin_x, const int& end_x) {
	std::random_device random_dev;
	std::mt19937 probability(random_dev());
	std::uniform_int_distribution<> range(begin_x, end_x);
	return range(probability);
}

void GenerateRandomFile(const std::string& file_name) {
	std::ofstream random_numbers(file_name);

	std::cout << BOLD GREEN << "Enter amount of numbers to generate: " << RST;
	size_t numbers_count{};
	std::cin >> numbers_count;

	std::cout << BOLD GREEN << "Enter diapason of generated numbers {-2^31...2^31}: " << RST;
	int begin_x, end_x;
	std::cin >> begin_x >> end_x;

	if (begin_x > end_x) {
		throw std::invalid_argument("ERROR: WRONG INPUT!");
	}

	if (random_numbers.is_open()) {
		for (size_t i{}; i < numbers_count; ++i) {
			random_numbers << GenerateRandomInteger(begin_x, end_x) << std::endl;
		}
		random_numbers.close();
	}
}

int main() {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}