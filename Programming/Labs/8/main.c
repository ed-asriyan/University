#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "StackInt.h"
#include "StackChar.h"

bool IsOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

bool IsValidSymbol(char c) {
	char valid_symbols[] =
		"0123456789"
			"ABCDEFGHIGKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"+-*/%()^";

	for (size_t i = 0; i < sizeof(valid_symbols) - 1; ++i) {

		if (c == valid_symbols[i]) {
			return true;
		}
	}

	return false;
}

bool IsUnary(char other, char op) {
	char operators[] =
		"+-*/(";

	for (size_t i = 0; i < sizeof(operators); ++i) {

		if (other == operators[i] && (op == '+' || op == '-')) {
			return true;
		}
	}

	return false;
}

int Priority(char op) {
	if (op < 0) {
		return 4;
	}

	return op == '+' || op == '-' ? 1 :
	       op == '*' || op == '/' || op == '%' ? 2 :
	       op == '^' ? 3 : -1;
}

void ProcessOperation(IntStack* stack, char op) {
	if (op < 0) {
		int left = pop(stack);

		switch (-op) {

			case '+': push(stack, left);
				break;

			case '-': push(stack, -left);
				break;
		}
	} else {
		int right = pop(stack);
		int left = pop(stack);

		switch (op) {

			case '+': push(stack, left + right);
				break;

			case '-': push(stack, left - right);
				break;

			case '*': push(stack, left * right);
				break;

			case '/': push(stack, left / right);
				break;

			case '%': push(stack, left % right);
				break;

			case '^': push(stack, pow(left, right));
				break;
		}
	}
}

int IsIn(char ch, char* alphabet) {
	for (size_t i = 0; i < strlen(alphabet); ++i) {

		if (ch == alphabet[i]) {
			return i;
		}
	}

	return -1;
}

/* return a new string with every instance of ch replaced by repl */
char* replace(const char* s, char ch, const char* repl) {
	int count = 0;
	const char* t;
	for (t = s; *t; t++)
		count += (*t == ch);

	size_t rlen = strlen(repl);
	char* res = malloc(strlen(s) + (rlen - 1) * count + 1);
	char* ptr = res;
	for (t = s; *t; t++) {
		if (*t == ch) {
			memcpy(ptr, repl, rlen);
			ptr += rlen;
		} else {
			*ptr++ = *t;
		}
	}
	*ptr = 0;
	return res;
}

int main() {
	CharStack* expression = Constructor();
	char current_symbol;

	while (true) {
		current_symbol = fgetc(stdin);

		if (current_symbol == '\n') {
			break;
		}

		if (IsValidSymbol(current_symbol)) {
			Push(expression, current_symbol);
		}
	}

	char vars[53] = "";
	int values[52];

	int k = 0;

	for (int i = 0; i < Size(expression); ++i) {
		if (isalpha(expression->base[i])) {

			int code = IsIn(expression->base[i], vars);

			if (code == -1) {
				fprintf(stdout, "%c = ", expression->base[i]);
				int temp;
				fscanf(stdin, "%d", &temp);

				char tmp[100];
				sprintf(tmp, "%d", temp);
				char* e = replace(expression->base, expression->base[i], tmp);
				vars[k] = expression->base[i];
				vars[k + 1] = '\0';
				values[k] = temp;

				free(expression->base);
				expression->base = e;
				expression->stack_size = expression->base_size = strlen(e);
				++k;
			} else {
				expression->base[i] = values[code] + '0';
			}
		}
	}

	IntStack* variables = constructor();
	CharStack* operators = Constructor();
	bool may_unary = true;

	for (int i = 0; i < Size(expression); ++i) {

		if (expression->base[i] == '(') {
			Push(operators, expression->base[i]);
			may_unary = true;
		} else if (expression->base[i] == ')') {

			while (Top(operators) != '(') {
				ProcessOperation(variables, Pop(operators));
			}

			Pop(operators);
		} else if (IsOperator(expression->base[i])) {

			if (may_unary && IsUnary(expression->base[i - 1], expression->base[i])) {
				expression->base[i] = -expression->base[i];
			}

			while (!Empty(operators) && (
				(expression->base[i] >= 0 && Priority(Top(operators)) >= Priority(expression->base[i]))
					|| (expression->base[i] < 0 && Priority(Top(operators)) > Priority(expression->base[i])))) {
				ProcessOperation(variables, Pop(operators));
			}

			Push(operators, expression->base[i]);
			may_unary = true;
		} else {
			CharStack* operand = Constructor();

			while (i < Size(expression) && isalnum(expression->base[i])) {
				Push(operand, expression->base[i++]);
			}

			--i;
			operand->base[Size(operand)] = '\0';

			if (isdigit(operand->base[0])) {
				push(variables, atoi(operand->base));
			}

			Destructor(operand);
			may_unary = false;
		}
	}

	while (!Empty(operators)) {
		ProcessOperation(variables, Pop(operators));
	}

	printStack(variables);

	Destructor(operators);
	destructor(variables);
	Destructor(expression);

	return 0;
}