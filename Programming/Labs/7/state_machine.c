#include "state_machine.h"

void format_to_xml(FILE* output_stream,
                   char* token_category,
                   char* token_name,
                   int number_of_line,
                   int position,
                   int length) {
	fprintf(output_stream, "\t<Token>\n");
	fprintf(output_stream, "\t\t<Category_of_token>%s</Category_of_token>\n", token_category);
	fprintf(output_stream, "\t\t<Name_of_token>%s</Name_of_token>\n", token_name);
	fprintf(output_stream, "\t\t<Number_of_line>%d</Number_of_line>\n", number_of_line);
	fprintf(output_stream, "\t\t<Position_in_line>%d</Position_in_line>\n", position);
	fprintf(output_stream, "\t\t<Length_name_of_token>%d</Length_name_of_token>\n", length);
	fprintf(output_stream, "\t</Token>\n");
}

int is_key(const char* word) {
	char* keywords[NUMBER_OF_KEYWORDS] = {
		"auto", "break", "case", "char", "const",
		"continue", "default", "do", "double",
		"else", "enum", "extern", "float", "for",
		"goto", "if", "inline", "int", "long",
		"register", "restrict", "return", "short",
		"signed", "sizeof", "static", "struct",
		"switch", "typedef", "union", "unsigned",
		"void", "volatile", "while", "_Bool",
		"_Complex", "_Imaginary", "int"
	};

	for (int i = 0; i < NUMBER_OF_KEYWORDS; ++i) {

		if (strcmp(word, keywords[i]) == 0) {

			return 1;
		}
	}

	return 0;
}

int is_operator(const char* operator) {
	char* operators[NUMBER_OF_OPERATORS] = {
		"++", "--", "&", "*", "+", "-", "!", "/",
		"%", "<<", ">>", "<", ">", "<=", ">=", "==",
		"!=", "^", "&&", "||", "?", "=", "*=", "/=",
		"%=", "+=", "-=", "&=", "^=", "|="
	};

	for (int i = 0; i < NUMBER_OF_OPERATORS; ++i) {

		if (strcmp(operator, operators[i]) == 0) {

			return 1;
		}
	}

	return 0;
}

int is_right_bracket(char ch) {
	return ch == ')' || ch == ']' || ch == '}';
}

int is_left_bracket(char ch) {
	return ch == '(' || ch == '[' || ch == '{';
}

state_t hightlight_tokens(FILE* output_stream, Stack* line, state_t state, int number_of_line) {
	int current_position = 0;

	for (const char* s = line->base; s < line->base + size(line); ++s) {
		Stack* buffer = create_stack();

		if (s[0] == '\t') {
			current_position += 4;
		} else {
			++current_position;
		}

		switch (state) {

			case ST_USUAL:

				if (s[0] == '#' || line->base[0] == '\n' || (s[0] == '/' && s[1] == '/')) {
					return ST_USUAL;
				} else if (s[0] == '/' && s[1] == '*') {
					state = ST_MULTILINE_COMMENT;
					++s;
				} else {

					if (s[0] == '"') {
						state = ST_STRING_LITERAL;
						--current_position;
						--s;
					} else if (ispunct(s[0])) {
						state = ST_PUNCTUATOR;
						--current_position;
						--s;
					} else if (isdigit(s[0])) {
						state = ST_CONSTANT;
						--current_position;
						--s;
					} else if (isalpha(s[0])) {
						state = ST_IDENTIFIER;
						--current_position;
						--s;
					}
				}

			case ST_MULTILINE_COMMENT:

				if (s[0] == '*' && s[1] == '/') {
					state = ST_USUAL;
					++s;

					continue;
				}

				break;

			case ST_STRING_LITERAL:

				while (1) {
					push_stack(buffer, s[0]);
					++s;

					if (s[0] == '"') {
						push_stack(buffer, s[0]);

						break;
					}
				}

				push_stack(buffer, '\0');
				format_to_xml(output_stream,
				              "String literal",
				              buffer->base,
				              number_of_line,
				              current_position,
				              size(buffer) - 1);
				current_position += size(buffer) - 2;
				state = ST_USUAL;

				break;

			case ST_PUNCTUATOR: push_stack(buffer, s[0]);

				if (ispunct(s[1]) && !is_right_bracket(s[1]) && !is_left_bracket(s[1]) && s[1] != ';' && s[1] != '"') {
					++s;
					push_stack(buffer, s[0]);
				}

				push_stack(buffer, '\0');

				if (is_right_bracket(buffer->base[0])) {
					format_to_xml(output_stream,
					              "Closing bracket",
					              buffer->base,
					              number_of_line,
					              current_position,
					              size(buffer) - 1);
				} else if (is_left_bracket(buffer->base[0])) {
					format_to_xml(output_stream,
					              "Openning bracket",
					              buffer->base,
					              number_of_line,
					              current_position,
					              size(buffer) - 1);
				} else if (is_operator(buffer->base)) {
					format_to_xml(output_stream,
					              "Operator",
					              buffer->base,
					              number_of_line,
					              current_position,
					              size(buffer) - 1);
				} else {
					format_to_xml(output_stream,
					              "Punctuator",
					              buffer->base,
					              number_of_line,
					              current_position,
					              size(buffer) - 1);
				}

				current_position += size(buffer) - 2;
				state = ST_USUAL;

				break;

			case ST_CONSTANT: push_stack(buffer, s[0]);
				push_stack(buffer, '\0');
				format_to_xml(output_stream, "Integer constant", buffer->base, number_of_line, current_position, 1);
				state = ST_USUAL;

				break;

			case ST_IDENTIFIER:

				while (1) {
					push_stack(buffer, s[0]);
					++s;

					if (isdigit(s[0]) || ispunct(s[0]) || isspace(s[0])) {
						--s;

						break;
					}
				}

				push_stack(buffer, '\0');
				int is_keyword = is_key(buffer->base);

				if (is_keyword) {
					format_to_xml(output_stream,
					              "Keyword",
					              buffer->base,
					              number_of_line,
					              current_position,
					              size(buffer) - 1);
				} else {
					format_to_xml(output_stream,
					              "Identifier",
					              buffer->base,
					              number_of_line,
					              current_position,
					              size(buffer) - 1);
				}

				current_position += size(buffer) - 2;
				state = ST_USUAL;

				break;
		}

		free_stack(buffer);
	}

	return state;
}

void get_line(FILE* input_stream, Stack* buffer_string, int* index) {
	char buffer_char;

	while (1) {
		++(*index);
		buffer_char = (char) fgetc(input_stream);
		push_stack(buffer_string, buffer_char);

		if (buffer_char == '\n') {
			pop_stack(buffer_string);

			break;
		}
	}
}

void read_from_stream(FILE* input_stream, FILE* output_stream) {
	int current_index = 0;
	int current_line = 0;
	char buffer_char;
	state_t state = ST_USUAL;

	while (1) {
		buffer_char = (char) fgetc(input_stream);
		++current_index;
		++current_line;

		if (buffer_char == EOF) {

			break;
		}

		fseek(input_stream, --current_index, SEEK_SET);

		Stack* buffer_string = create_stack();
		get_line(input_stream, buffer_string, &current_index);

		state = hightlight_tokens(output_stream, buffer_string, state, current_line);
		free_stack(buffer_string);
	}
}