#ifndef __TESTS_HPP_DEF__
#define __TESTS_HPP_DEF__

#include <iostream>
#include <iomanip>
#include <ctime>

#include "CStack_Array.hpp"
#include "CStack_List.hpp"
#include "timer.h"

namespace TestGenerator {
	const int int_min =  1;
	const int int_max =  5;
	const int str_len =  4;

	int GetRandomInteger() {
		return rand() % 100 + (int_max - int_min) + int_min;
	}

	std::string GetRandomString() {
		char alphabet[] = 
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";

		std::string str;
		for (int i = 0; i < str_len; ++i) {
			str.push_back(alphabet[rand() % sizeof(alphabet)]);
		}

		return str;
	}

	template <template <typename> class STACK>
	STACK<int> GenerateIntegerData(int size) {
		STACK<int> stack;
		srand(time(nullptr));

		for (int i = 0; i < size; ++i) {
			stack.Push(GetRandomInteger());
		}

		return stack;
	}

	template <template <typename> class STACK>
	STACK<double> GenerateDoubleData(int size) {
		STACK<double> stack;
		srand(time(nullptr));

		for (int i = 0; i < size; ++i) {
			stack.Push((double)GetRandomInteger() / GetRandomInteger() * GetRandomInteger());
		}

		return stack;
	}

	template <template <typename> class STACK>
	STACK<char> GenerateCharacterData(int size) {
		STACK<char> stack;
		srand(time(nullptr));

		char alphabet[] = 
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";

		for (int i = 0; i < size; ++i) {
			stack.Push(alphabet[rand() % sizeof(alphabet)]);
		}

		return stack;
	}

	template <template <typename> class STACK>
	STACK<std::string> GenerateStringData(int size) {
		STACK<std::string> stack;
		srand(time(nullptr));

		for (int i = 0; i < size; ++i) {
			stack.Push(GetRandomString());
		}

		return stack;
	}

	template <class STACK>
	void ClearStack(STACK& stack) {
		int size = stack.size();
		for (int i = 0; i < size; ++i) {
			stack.Pop();
		}
	}

	template <typename T, template <typename> class STACK>
	double MergeCreationTime(STACK<T> (*Generator)(int), STACK<T>& stack, int size) {
		Timer t;
		double start_timer, stop_timer;

		t.start();
		start_timer = t.getElapsedTime();
		stack = Generator(size);
		stop_timer = t.getElapsedTime();
		t.stop();

		return stop_timer - start_timer;
	}

	template <class STACK>
	double MergeDeletionTime(STACK& stack) {
		Timer t;
		double start_timer, stop_timer;

		t.start();
		start_timer = t.getElapsedTime();
		ClearStack(stack);
		stop_timer = t.getElapsedTime();
		t.stop();

		return stop_timer - start_timer;		
	}

	const int spaces = 12;

	void PrintLine(std::ostream& out) {
		for (int i = 0; i < spaces * 6; ++i) {
			out << '-';
		}

		out << std::endl;
	}

	void PrintHeader(std::ostream& out) {
		out << std::setw(spaces) << "SIZE"
			<< std::setw(spaces) << "Operation"
		  	<< std::setw(spaces) << "Integers"
			<< std::setw(spaces) << "Doubles"
			<< std::setw(spaces) << "Characters"
			<< std::setw(spaces) << "Strings" << std::endl;
	}

	template <template <typename> class STACK>
	void GenerateTests(std::ostream& out) {
		const int SIZES[] = {10, 100, 1000, 10000, 100000, 1000000};

		PrintLine(out);
		PrintHeader(out);
		PrintLine(out);

		for (int i = 0; i < (int)(sizeof(SIZES) / sizeof(*SIZES)); ++i) {
			STACK<int> int_stack;
			STACK<double> double_stack;
			STACK<char> char_stack;
			STACK<std::string> str_stack;

			out << std::setw(spaces) << SIZES[i]
				<< std::setw(spaces) << "Push"
				<< std::setw(spaces) << MergeCreationTime(GenerateIntegerData<STACK>, int_stack, SIZES[i])
				<< std::setw(spaces) << MergeCreationTime(GenerateDoubleData<STACK>, double_stack, SIZES[i])
				<< std::setw(spaces) << MergeCreationTime(GenerateCharacterData<STACK>, char_stack, SIZES[i])
				<< std::setw(spaces) << MergeCreationTime(GenerateStringData<STACK>, str_stack, SIZES[i]) << std::endl;

			out << std::setw(spaces) << SIZES[i]
				<< std::setw(spaces) << "Pop"
				<< std::setw(spaces) << MergeDeletionTime(int_stack)
				<< std::setw(spaces) << MergeDeletionTime(double_stack)
				<< std::setw(spaces) << MergeDeletionTime(char_stack)
				<< std::setw(spaces) << MergeDeletionTime(str_stack) << std::endl;

			PrintLine(out);
		}
	}
}

namespace Tests {
	template <template <typename> class STACK>
	void PushAndPop(std::ostream& out) {
		TestGenerator::GenerateTests<STACK>(out);
	}

	void TestPushAndPop(std::ostream& out) {
		PushAndPop<CStackArray>(out);
		out << std::endl;
		PushAndPop<CStackList>(out);
	}

	const int size = 10;

	template <typename T, template <typename> class STACK>
	void TestMemoryAllocation(std::ostream& out) {
		STACK<T> stack;

		stack = TestGenerator::GenerateIntegerData<STACK>(size);
		stack.TrackMemory(out);

		TestGenerator::ClearStack(stack);

		stack = TestGenerator::GenerateIntegerData<STACK>(size);
		stack.TrackMemory(out);
	}

	void TestMemory(std::ostream& out) {
		out << "MEMORY TESTS:" << std::endl;
		out << "Stack with dynamically cycled buffer." << std::endl;

		TestMemoryAllocation<int, CStackArray>(out);

		out << std::endl;

		out << "Stack created on doubly-linked list." << std::endl;

		TestMemoryAllocation<int, CStackList>(out);
	}
}

#endif // __TESTS_HPP_DEF__