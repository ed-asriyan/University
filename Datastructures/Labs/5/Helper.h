//
// Created by ed on 21.11.16.
//

#ifndef MATRIX_HELPER_H
#define MATRIX_HELPER_H

#include <ostream>
#include <sstream>
#include <string>

namespace Helper {
	/**
	 * @brief Contecate two streams by rows.
	 * @param os Output stream.
	 * @param a Left input stream.
	 * @param b Right input stream.
	 *
	 * a:
	 * 1 2 3
	 * 4 5 6
	 *
	 * b:
	 * a b c
	 * d e
	 *
	 * os:
	 * 1 2 3  | a b c
	 * 4 5 6  | d e
	 */
	template<class A, class B>
	void ContecateStreamByRows(std::ostream& os, const A& a, const B& b) {
		std::stringstream a_s;
		a_s << a;

		std::stringstream b_s;
		b_s << b;

		auto a_str = a_s.str();
		auto b_str = b_s.str();

		auto b_it = b_str.cbegin();
		for (auto& a_c: a_str) {
			if (a_c == '\n') {
				os << "   | ";
				while (b_it != b_str.end() && *b_it != '\n') {
					os << *b_it;
					++b_it;
				}
				if (b_it != b_str.end()) {
					++b_it;
				}
			}
			os << a_c;
		}
	}
}

#endif //MATRIX_HELPER_H
