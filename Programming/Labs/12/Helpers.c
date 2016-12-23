//
// Created by lieroz on 04.12.16.
//

#include "Helpers.h"

void ScanInput(char* buffer, size_t size, const char* name, bool is_null) {
	fprintf(stdout, "Enter %s: ", name);
	getline(&buffer, &size, stdin);
	buffer[strlen(buffer) - 1] = '\0';

	if (!is_null) {

		while (strlen(buffer) == 0) {
			fprintf(stdout, "Enter %s: ", name);
			getline(&buffer, &size, stdin);
			buffer[strlen(buffer) - 1] = '\0';
		}
	}
}

bool SearchForPrimaryKey(int primary_key, const char* file_name, const char* tag_name) {
	xmlDoc* file = xmlReadFile(file_name, NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	xmlChar* temp = NULL;

	int compared_key = 0;
	bool flag = false;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST tag_name)) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == primary_key) {
					flag = true;
				}
			}
		}
	}

	xmlFree(temp);
	xmlFree(root);
	xmlFree(file);

	return flag;
}

bool SearchForPair(int supplier_id, int product_id) {
	xmlDoc* file = xmlReadFile("Examples/XML_Shipments.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	xmlChar* temp_supplier = NULL;
	xmlChar* temp_product = NULL;

	int compared_sup = 0;
	int compared_prod = 0;
	bool flag = false;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "SupplierID") && !xmlStrcmp(j->next->name, BAD_CAST "ProductID")) {
				temp_supplier = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp_supplier, "%d", &compared_sup);

				temp_product = xmlNodeListGetString(file, j->next->children, 1);
				sscanf((const char*) temp_product, "%d", &compared_prod);

				if (compared_sup == supplier_id && compared_prod == product_id) {
					flag = true;
				}
			}
		}
	}

	xmlFree(temp_supplier);
	xmlFree(temp_product);
	xmlFree(root);
	xmlFree(file);

	return flag;
}