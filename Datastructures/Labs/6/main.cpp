#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

#include "NaiveTree.h"
#include "File.h"
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

int main(const int argc, const char* argv[]) {
	if (argc != 2) {
		throw std::invalid_argument("ERROR: NO INPUT FILE!");
	}

	std::string file_name{argv[1]};

	std::cout << BOLD GREEN << "Do you want to generate new Random data? {1/0}: " << RST;
	int choice{};
	std::cin >> choice;

	if (choice == 1) {
		try {
			GenerateRandomFile(file_name);
		} catch (...) {
			std::cerr << "ERROR! SOMETHING WENT WRONG, PLEASE CONTACT THE ADMINISTRATOR!" << std::endl;
			return -1;
		}
	}

	NaiveTree<int> tree;

	std::ifstream input_file(file_name);
	while (!input_file.eof()) {
		int item;
		input_file >> item;
		tree.Insert(item);
	}
	input_file.close();

	File<int> file(file_name);

	bool is_running = true;
	while (is_running) {
		std::cout << BOLD GREEN << "Choose the action:" << RST << std::endl;
		std::cout << BOLD << " 1. Add item" << RST << std::endl;
		std::cout << BOLD << " 2. Remove item from tree" << RST << std::endl;
		std::cout << BOLD << " 3. Search for item" << RST << std::endl;
		std::cout << BOLD << " 4. Print tree" << RST << std::endl;
		std::cout << BOLD << " 5. Print by level" << RST << std::endl;
		std::cout << BOLD << " 0. Exit" << RST << std::endl;
		std::cout << BOLD << ": ";

		std::chrono::time_point<std::chrono::system_clock> tree_start, tree_stop, file_start, file_stop;
		bool is_tree_measure = false;
		bool is_file_measure = false;

		int action;
		std::cin >> action;
		int item;
		switch (action) {
			case 1:
				std::cout << BOLD CYAN << "Enter item: " << RST;
				std::cin >> item;

				tree_start = std::chrono::system_clock::now();
				tree.Insert(item);
				tree_stop = std::chrono::system_clock::now();

				file_start = std::chrono::system_clock::now();
				file.Insert(item);
				file_stop = std::chrono::system_clock::now();

				is_tree_measure = true;
				is_file_measure = true;
				break;
			case 2:
				std::cout << BOLD CYAN << "Enter item: " << RST;
				std::cin >> item;
				try {
					tree_start = std::chrono::system_clock::now();
					tree.Remove(item);
					tree_stop = std::chrono::system_clock::now();

					is_tree_measure = true;
				} catch (BaseTree<int>::ItemNotFoundException& e) {
					std::cout << BOLD RED << "Item not found!" << RST << std::endl;
				}
				break;
			case 3:
				std::cout << BOLD CYAN << "Enter item: " << RST;
				std::cin >> item;
				try {
					tree_start = std::chrono::system_clock::now();
					tree.Search(item);
					tree_stop = std::chrono::system_clock::now();

					file_start = std::chrono::system_clock::now();
					file.Insert(item);
					file_stop = std::chrono::system_clock::now();

					is_tree_measure = true;
					is_file_measure = true;
				} catch (BaseTree<int>::ItemNotFoundException& e) {
					std::cout << BOLD RED << "Item not found!" << RST << std::endl;
				}
				break;
			case 4:
				std::cout << BOLD BLUE << tree << RST << std::endl;

				std::cout << BOLD GREEN << "DFS pre-order: " << BOLD CYAN;
				tree.Dfs<-1>([](const int& i) {
					std::cout << i << ' ';
				});
				std::cout << RST << std::endl;

				std::cout << BOLD GREEN << "DFS in-order: " << BOLD CYAN;
				tree.Dfs<0>([](const int& i) {
					std::cout << i << ' ';
				});
				std::cout << RST << std::endl;

				std::cout << BOLD GREEN << "DFS post-order: " << BOLD CYAN;
				tree.Dfs<1>([](const int& i) {
					std::cout << i << ' ';
				});
				std::cout << RST << std::endl;
				break;
			case 5:
				std::cout << BOLD GREEN << "Count by level: " << BOLD BLUE;
				for (auto count: tree.CountByLevel()) {
					std::cout << count << ' ';
				}
				std::cout << RST << std::endl;
				break;
			default:
				is_running = false;
		}

		if (is_tree_measure) {
			std::cout << BOLD GREEN << "Amount of time taken to do action element on Tree: "
			          << BOLD BLUE
			          << std::chrono::duration_cast<std::chrono::nanoseconds>(tree_stop - tree_start).count() << " (ns)"
			          << RST << std::endl;
		}
		if (is_file_measure) {
			std::cout << BOLD GREEN << "Amount of time taken to do action element on File: "
			          << BOLD BLUE
			          << std::chrono::duration_cast<std::chrono::nanoseconds>(file_stop - file_start).count() << " (ns)"
			          << RST << std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}