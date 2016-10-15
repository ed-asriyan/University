//
// Created by ed on 05.10.16.
//

#include <stdio.h>

#include "XML/xml_object.h"
#include "customer.h"
#include "customer_container.h"

char search_key[50] = "";

int cmpTitle(Customer* x) {
	return strcmp(search_key, get_customer_title(x));
}

int cmpFirstName(Customer* x) {
	return strcmp(search_key, get_customer_first_name(x));
}

int cmpLastName(Customer* x) {
	return strcmp(search_key, get_customer_last_name(x));
}

const char* CMP_FUNCTION_NAMES[] = {"Title", "first name", "last name"};

int (* CMP_FUNCTIONS[])(Customer*, Customer*) = {CustomerCmpTitle, CustomerCmpFirstName, CustomerCmpLastName};

int (* CMP_VAL_FUNCTIONS[])(Customer*) = {cmpTitle, cmpFirstName, cmpLastName};

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

			int cmp_func_id = -1;
			do {
				printf("Choose the sorting key\n");
				for (int i = 0; i < sizeof(CMP_FUNCTIONS) / sizeof(CMP_FUNCTIONS[0]); ++i) {
					printf("\t%d (%s)\n", i, CMP_FUNCTION_NAMES[i]);
				}
				printf(": ");

				scanf("%d", &cmp_func_id);
			} while (cmp_func_id < 0 || cmp_func_id >= sizeof(CMP_FUNCTIONS) / sizeof(CMP_FUNCTIONS[0]));

			const int (* cmp_func)(Customer*, Customer*) = CMP_FUNCTIONS[cmp_func_id];
			const char* cmp_func_name = CMP_FUNCTION_NAMES[cmp_func_id];

			printf("Sorting %d customers by %s...\n", customers_count, cmp_func_name);
			MergeSort(customers, customers_count, cmp_func);

			printf("\nEnter search key: ");
			scanf("%s", search_key);
			Customer* c = Search(customers, customers_count, CMP_VAL_FUNCTIONS[cmp_func_id]);

			if (c == NULL) {
				printf("Nothing was found");
			} else {
				printf("%d %s %s %s %s %s %s\n",
				       get_customer_id(c),
				       get_customer_title(c),
				       get_customer_first_name(c),
				       get_customer_last_name(c),
				       get_customer_company_name(c),
				       get_customer_email_address(c),
				       get_customer_phone(c));
			}

			FreeCustomerList(customers, customers_count);
		}

		FreeXmlObject(root);
	} else {
		printf("Error parsing xml root\n");
	}

	free(file_content);
	fclose(f);

	return 0;
}