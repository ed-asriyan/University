//
// Created by ed on 09.11.16.
//

#include "double_checker.h"

/**
 * @brief Сhecks whether a double string can contains the symbol
 * @param symbol Symbol which is necessary check for.
 * @return true if double string can contains the symbol; otherwise, false.
 */
int is_valid_char(char symbol) {
	char valid_symbols[] = "0123456789-+eE.";

	int size = sizeof(valid_symbols);
	for (int i = 0; i < size; ++i) {
		if (symbol == valid_symbols[i]) return 1;
	}

	return 0;
}

/**
 * @brief Сhecks whether a string is a valid double string.
 * @param number A string containing a number to check.
 * @return true if string is a valid double string; otherwise, false.
 */
int check_double_str(const char* number) {
	if (*number == '.' || *number == 'e') {
		return 0;
	}

	int e_pos = 0;
	int dot_pos = 0;
	int sign_pos = 0;
	int size = (int)strlen(number);
	for (int i = 0; i < size; ++i) {

		if (!is_valid_char(number[i])) {
			return 0;
		}

		if (number[i] == '.') {
			dot_pos = i;
		}

		if (number[i] == 'e' || number[i] == 'E') {
			e_pos = i;
		}

		if (number[i] == '+' || number[i] == '-') {
			sign_pos = i;
		}
	}

	if ((dot_pos == 0 && e_pos == 0)) {
		return 0;
	}

	if (e_pos != 0 && dot_pos > e_pos) {
		return 0;
	}

	if (e_pos == size - 1) {
		return 0;
	}

	if (sign_pos != 0 && (sign_pos - 1) != e_pos) {
		return 0;
	}

	return 1;
}
