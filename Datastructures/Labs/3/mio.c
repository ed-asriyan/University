#include "mio.h"

int input_positive_int(char* msg, int* ptr_i) {
	char c;
	int i;

	while (1) {
		printf("%s", msg);

		if (scanf("%d", &i) == 1) {
			if (i >= 0) {
				*ptr_i = i;
				return 0;
			} else {
				printf("Input error: negative number. Try again.\n");
				continue;
			}
		}

		do {
			c = getc(stdin);
			//scanf("%c", &c);

			if (c == EXIT_CHAR)
				return -1;
		} while (c != EOF);
		//while (c != '\n' && c != EOF);

		printf("Input error: not an integer. Try again.\n");
	}
}

int input_binary(char* msg, int* ptr_i) {
	char c;
	int i;

	while (1) {
		printf("%s", msg);

		if (scanf("%d", &i) == 1) {
			if (i == 0 || i == 1) {
				*ptr_i = i;
				return 0;
			} else
				printf("Input error: not a binary. Try again.\n");
		} else {
			do {
				scanf("%c", &c);

				if (c == EXIT_CHAR)
					return -1;
			} while (c != '\n' && c != EOF);

			printf("Input error: not a binary. Try again.\n");
		}
	}
}

int input_string(char* msg, char* str, int max_len) {
	char c;
	int found_zero;

	while (1) {
		printf("%s", msg);
		printf("(Max. %d characters)\n", max_len - 1);

		printf("<-");
		for (int i = 0; i < max_len - 5; i++)
			printf(" ");
		printf("->\n");

		while (1) {
			c = getc(stdin);

			if (c != '\n' && c != EOF) {
				ungetc(c, stdin);
				break;
			}
		}

		for (int i = 0; i < max_len; i++) {
			if (scanf("%c", &c) == 1) {
				if (c != '\n')
					str[i] = c;
				else {
					//printf("Point 1\n"); // Debug

					str[i] = 0;
					break;
				}

				if (c == 0) {
					//printf("Point 2\n"); // Debug

					break;
				}
			} else {
				//printf("Point 3\n"); // Debug

				str[i] = 0;
				break;
			}
		}

		while (c != '\n' && scanf("%c", &c) == 1);

		if (str[0] == EXIT_CHAR)
			return -1;

		found_zero = 0;
		for (int i = 0; i < max_len; i++)
			if (str[i] == 0)
				found_zero = 1;

		if (!found_zero)
			printf("Input error: too much characters. Try again.\n");
		else if (str[0] == 0)
			printf("Input error: empty string. Try again.\n");
		else
			return 0;
	}
}
