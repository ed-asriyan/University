//
// Created by lieroz on 05.12.16.
//

#include "ModifyTableContent.h"

void ModifySupplier(const char* file_name, const char* tag_name, xmlDoc* file, xmlNode* root, int primary_key) {
	xmlChar* temp = NULL;
	xmlNode** stack = (xmlNode**) malloc(sizeof(xmlNode*) * 128);
	size_t size = 256;
	char* buffer = malloc(sizeof(char) * size);
	int compared_key = 0;
	size_t count = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST tag_name)) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == primary_key) {
					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, false);
					xmlNewChild(i, 0, j->name, BAD_CAST buffer);


					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, false);
					int status = 0;

					while (sscanf(buffer, "%d", &status) != 1 || (status < 0 || status > 100)) {
						ScanInput(buffer, size, (const char*) j->name, false);
					}

					sprintf(buffer, "%d", status);
					xmlNewChild(i, 0, j->name, BAD_CAST buffer);


					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, false);
					xmlNewChild(i, 0, j->name, BAD_CAST buffer);
				}
			}
		}
	}

	for (size_t i = 0; i < count; ++i) {
		xmlUnlinkNode(stack[i]);
		xmlFree(stack[i]);
	}

	free(buffer);
	free(stack);
	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);
	xmlFree(temp);
}

void ModifyProduct(const char* file_name, const char* tag_name, xmlDoc* file, xmlNode* root, int primary_key) {
	xmlChar* temp = NULL;
	xmlNode** stack = (xmlNode**) malloc(sizeof(xmlNode*) * 128);
	size_t size = 256;
	char* buffer = malloc(sizeof(char) * size);
	int compared_key = 0;
	size_t count = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST tag_name)) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == primary_key) {
					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, false);
					xmlNewChild(i, 0, j->name, BAD_CAST buffer);


					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, true);

					if (strlen(buffer) != 0) {
						xmlNewChild(i, 0, j->name, BAD_CAST buffer);
					}

					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, true);
					double weight = 0;

					if (strlen(buffer) != 0) {

						while (sscanf(buffer, "%lf", &weight) != 1 || weight <= 0) {
							ScanInput(buffer, size, (const char*) j->name, true);

							if (strlen(buffer) == 0) {
								break;
							}
						}

						sprintf(buffer, "%.2lf", weight);
						xmlNewChild(i, 0, j->name, BAD_CAST buffer);
					}


					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, true);
					double price = 0;

					if (strlen(buffer) != 0) {

						while (sscanf(buffer, "%lf", &price) != 1 || price < 0) {
							ScanInput(buffer, size, (const char*) j->name, true);

							if (strlen(buffer) == 0) {
								break;
							}
						}

						sprintf(buffer, "%.2lf", price);
						xmlNewChild(i, 0, j->name, BAD_CAST buffer);
					}


					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, false);
					xmlNewChild(i, 0, j->name, BAD_CAST buffer);
				}
			}
		}
	}

	for (size_t i = 0; i < count; ++i) {
		xmlUnlinkNode(stack[i]);
		xmlFree(stack[i]);
	}

	free(buffer);
	free(stack);
	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);
	xmlFree(temp);
}

void ModifyShipment(const char* file_name, const char* tag_name, xmlDoc* file, xmlNode* root, int primary_key) {
	xmlChar* temp = NULL;
	xmlNode** stack = (xmlNode**) malloc(sizeof(xmlNode*) * 128);
	size_t size = 256;
	char* buffer = malloc(sizeof(char) * size);
	int compared_key = 0;
	size_t count = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST tag_name)) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == primary_key) {
					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, false);
					int supplier_id = 0;

					while (sscanf(buffer, "%d", &supplier_id) != 1
						|| !SearchForPrimaryKey(supplier_id, "Examples/XML_Suppliers.xml", "SupplierID")) {
						ScanInput(buffer, size, (const char*) j->name, false);
					}

					sprintf(buffer, "%d", supplier_id);
					xmlNewChild(i, 0, j->name, BAD_CAST buffer);


					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, false);
					int product_id = 0;

					while (sscanf(buffer, "%d", &product_id) != 1
						|| !SearchForPrimaryKey(product_id, "Examples/XML_Products.xml", (const char*) j->name)
						|| SearchForPair(supplier_id, product_id)) {
						ScanInput(buffer, size, (const char*) j->name, false);
					}

					sprintf(buffer, "%d", product_id);
					xmlNewChild(i, 0, j->name, BAD_CAST buffer);


					j = j->next;
					stack[count++] = j;
					ScanInput(buffer, size, (const char*) j->name, false);
					int qty = 0;

					while (sscanf(buffer, "%d", &qty) != 1 || qty <= 0) {
						ScanInput(buffer, size, (const char*) j->name, false);
					}

					sprintf(buffer, "%d", qty);
					xmlNewChild(i, 0, j->name, BAD_CAST buffer);
				}
			}
		}
	}

	for (size_t i = 0; i < count; ++i) {
		xmlUnlinkNode(stack[i]);
		xmlFree(stack[i]);
	}

	free(buffer);
	free(stack);
	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);
	xmlFree(temp);
}

void ModifyTableContent(const char* file_name,
                        const char* tag_name,
                        int primary_key,
                        void (* modify)(const char*, const char*, xmlDoc*, xmlNode*, int)) {
	xmlDoc* file = xmlReadFile(file_name, NULL, 1);
	xmlNode* root = xmlDocGetRootElement(file);

	modify(file_name, tag_name, file, root, primary_key);
//	modify(NULL, tag_name, file, root, primary_key);

	xmlFree(root);
	xmlFree(file);
}