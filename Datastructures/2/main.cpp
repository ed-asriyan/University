#include <iostream>
#include <fstream>
#include <algorithm>

#include "CStack_Array.hpp"
#include "CStack_List.hpp"
#include "tests.hpp"

template <typename T, template <typename> class STACK>
bool IsPalindrome(STACK<T>& stack) {
	STACK<T> temp_stack;

	for (int i = 0; i < (stack.size() + 1) / 2; ++i) {
		temp_stack.Push(stack[i]);
	}

	for (int i = stack.size() / 2; i < stack.size(); ++i) {
		if (temp_stack.Pop() != stack[i]) {
			return false;
		}
	}

	return true;
}

template <typename T, template <typename> class STACK>
void UserCommands(STACK<T>& stack) {

	while (true) {
		int command = 0;
		T value = 0;

		std::cout << "Stack: " << stack << std::endl;
		std::cout << "This string is " << (IsPalindrome<T, STACK>(stack) ? "" : "not ") << "a palindrome" << std::endl;


		std::cout << std::endl << "Work with stack {0, 1, 2, 3} {exit, push, pop, tests}: " << std::endl;
		std::cin >> command;

		switch (command) {
			case 0:
				return;

			case 1:
			std::cin >> value;
				stack.Push(value);		
				break;
			case 2:
				value = stack.Pop();
				break;
			case 3:
				Tests::PushAndPop<STACK>(std::cout);
			 	break;
			 default: break;
		}
	}
}

int main() {
	try {
		std::cout << "Choose {0, 1} for stack on {array, list}: ";

		int choice = 0;
		std::cin >> choice;
		std::getchar();

		std::cout << std::endl << "Input string: ";

		if (choice == 0) {
			CStackArray<char> stack;
			std::cin >> stack;

			UserCommands<char, CStackArray>(stack);
		} else if (choice == 1) {
			CStackList<char> stack;
			std::cin >> stack;

			UserCommands<char, CStackList>(stack);
		} else {
			throw std::invalid_argument("ERROR: IVALID ARMUNENT OF CHOICE!!!");
		}
	} catch (std::exception& ex) {
		std::cout << "ERROR: " << ex.what() << std::endl;
	}

	return 0;
}