//
// Created by ed on 18.04.17.
//

#ifndef LAB2_ERRORS_HPP
#define LAB2_ERRORS_HPP

#include <exception>

class InvalidSizeException : public std::exception {
	public:
		const char* what() const noexcept override { return "invalid size"; }
};

class DivisionByZeroException : public std::exception {
	public:
		const char* what() const noexcept override { return "division by zero"; }
};

class IndexOutOfRangeException : public std::exception {
	public:
		const char* what() const noexcept override { return "index out of range"; }
};

#endif //LAB2_ERRORS_HPP
