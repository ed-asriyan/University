//
// Created by ed on 18.04.17.
//

#ifndef LAB2_ERRORS_HPP
#define LAB2_ERRORS_HPP

#include <exception>

class UnknownError : public std::exception {
	public:
		const char* what() const noexcept override { return "unknown error"; }
};

class MemoryError : public std::exception {
	public:
		const char* what() const noexcept override { return "memory error"; }
};

class SizeError : public std::exception {
	public:
		const char* what() const noexcept override { return "invalid size"; }
};

class ZeroDivisionError : public std::exception {
	public:
		const char* what() const noexcept override { return "division by zero"; }
};

#endif //LAB2_ERRORS_HPP
