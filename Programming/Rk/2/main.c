#include <stdio.h>
#include <ctype.h>

#define ABS(a) ((a) > 0 ? (a) : -(a))

int sign(int a) {
	if (a < 0) return -1;
	if (a > 0) return 1;
	return 0;
}

int is_operand(char c) {
	switch (c) {
		case '+': return 1;
		case '-': return 2;
		case '*': return -1;
		case '/': return -2;
		default: return 0;
	}
}

int is_digit(char c) {
	return isdigit(c);
}

int is_bracket(char c) {
	switch (c) {
		case '[': return 1;
		case ']': return -1;
		case '{': return 2;
		case '}': return -2;
		case '(': return 3;
		case ')': return -3;
		default: return 0;
	}
}

int check_expression(FILE* in) {
	int brackets[4] = {0, 0, 0};

	int prev_is_operand = 0;
	int prev_is_didit = 0;
	int prev_is_bracket = 0;

	char prev_c = '\0';
	char curr_c;
	while (fscanf(in, "%c", &curr_c) == 1 && curr_c != '\0' && curr_c != '\n') {
		int curr_is_operand = is_operand(curr_c);
		int curr_is_digit = is_digit(curr_c);
		int curr_is_bracket = is_bracket(curr_c);

		if (curr_is_operand) {
			if (curr_is_operand != 2) {
				if (prev_c == '\0') {
					return 0;
				} else if (sign(curr_is_operand) == sign(prev_is_operand)) {
					return 0;
				}
			}
		} else if (curr_is_bracket) {
			if (curr_is_bracket > 0) {
				if (prev_is_didit) {
					return 0;
				}
			} else {
				if (prev_is_operand) {
					return 0;
				}
			}
			brackets[ABS(curr_is_bracket)] += sign(curr_is_bracket);

			for (int i = 1; i < 4; ++i) {
				if (brackets[i] < 0) {
					return 0;
				}
			}
		} else if (curr_is_digit) {
			if (prev_is_bracket < 0) {
				return 0;
			}
		}

		prev_c = curr_c;
		prev_is_operand = curr_is_operand;
		prev_is_didit = curr_is_digit;
		prev_is_bracket = curr_is_bracket;
	}

	if (prev_is_operand) return 0;

	return 1;
}

int main() {
	printf(check_expression(stdin) ? "YES" : "NO");
	printf("\n");
	return 0;
}