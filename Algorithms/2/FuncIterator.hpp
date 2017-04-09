//
// Created by ed on 09.04.17.
//

#ifndef LAB2_FUNCITERATOR_HPP
#define LAB2_FUNCITERATOR_HPP

#include <functional>

#include "Point2d.h"

class FuncIterator {
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef Point2d value_type;
		typedef int difference_type;
		typedef Point2d* pointer;
		typedef Point2d& reference;
		typedef const Point2d* const_pointer;
		typedef const Point2d& const_reference;

		static std::pair<FuncIterator, FuncIterator> Create(
			const std::function<double(double)>& func,
			double begin,
			double end,
			int n
		);

		const_reference operator*() const;
		const_pointer operator->() const;

		difference_type operator-(const FuncIterator&) const;

		FuncIterator operator+(size_t) const;
		FuncIterator operator-(size_t) const;

		FuncIterator operator++(int);
		FuncIterator& operator++();
		FuncIterator operator--(int);
		FuncIterator& operator--();

		FuncIterator& operator=(const FuncIterator&);

		bool operator==(const FuncIterator& it) const;
		bool operator!=(const FuncIterator& it) const;

	private:
		FuncIterator(const std::function<double(double)>& func, double begin, int i, double step);

		double reCalc();

		const std::function<double(double)> func;
		double begin;
		int i;
		double step;
		Point2d point;
};

#endif //LAB2_FUNCITERATOR_HPP
