//
// Created by ed on 09.04.17.
//

#include "FuncIterator.hpp"

std::pair<FuncIterator, FuncIterator> FuncIterator::Create(
	const std::function<double(double)>& func,
	double begin,
	double end,
	int n
) {
	auto step = (end - begin) / n;
	FuncIterator begin_iterator(func, begin, 0, step);
	FuncIterator end_iterator(func, begin, n + 1, step);
	return std::pair<FuncIterator, FuncIterator>(begin_iterator, end_iterator);
}

FuncIterator::FuncIterator(const std::function<double(double)>& func, double begin, int i, double step)
	: func(func), begin(begin), i(i), step(step) {
	reCalc();
}

double FuncIterator::reCalc() {
	point.x = begin + i * step;
	point.y = func(point.x);
}

FuncIterator::difference_type FuncIterator::operator-(const FuncIterator& it) const {
	return i - it.i;
}

FuncIterator::const_reference FuncIterator::operator*() const {
	return point;
}

FuncIterator FuncIterator::operator+(size_t n) const {
	return FuncIterator(func, begin, i + static_cast<int>(n), step);
}

FuncIterator FuncIterator::operator-(size_t n) const {
	return FuncIterator(func, begin, i - static_cast<int>(n), step);
}

FuncIterator FuncIterator::operator++(int) {
	FuncIterator result = *this;
	++result;
	return result;
}

FuncIterator& FuncIterator::operator++() {
	++i;
	reCalc();
	return *this;
}

FuncIterator FuncIterator::operator--(int) {
	FuncIterator result = *this;
	--result;
	return result;
}

FuncIterator& FuncIterator::operator--() {
	--i;
	reCalc();
	return *this;
}

bool FuncIterator::operator==(const FuncIterator& it) const {
	return begin == it.begin && i == it.i && step == it.step;
}

bool FuncIterator::operator!=(const FuncIterator& it) const {
	return !(*this == it);
}

FuncIterator::const_pointer FuncIterator::operator->() const {
	return &point;
}

FuncIterator& FuncIterator::operator=(const FuncIterator& it) {
	begin = it.begin;
	i = it.i;
	point = it.point;
	return *this;
}
