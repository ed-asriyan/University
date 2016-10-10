//
// Created by ed on 05.10.16.
//

#include <stdio.h>

#include "XML/xml_object.h"
#include "customer.h"
#include "customer_container.h"

void ReadWholeFile(FILE* input_file, char** str) {
	char* file_contents;
	long input_file_size;
	fseek(input_file, 0, SEEK_END);
	input_file_size = ftell(input_file);
	rewind(input_file);
	file_contents = malloc(input_file_size * (sizeof(char)));
	fread(file_contents, sizeof(char), (size_t) input_file_size, input_file);

	*str = file_contents;
}

int main(void) {
	FILE* f = fopen("Customers.xml", "r");

	if (f == NULL) {
		fprintf(stderr, "Opening the file error\n");
		return -1;
	}

	char* file_content = NULL;
	ReadWholeFile(f, &file_content);

	XmlObject* root = ParseXml(file_content, NULL);

	if (root != NULL) {
		Customer** customers = NULL;
		int customers_count = ReadWholeCustomerList(root, &customers);

		if (customers != NULL) {
			// todo: main algorithm

			for (int i = 0; i < customers_count; ++i) {
				printf("%d ", get_customer_id(customers[i]));
			}

			FreeCustomerList(customers, customers_count);
		}

		FreeXmlObject(root);
	}

	free(file_content);
	fclose(f);

	return 0;
}