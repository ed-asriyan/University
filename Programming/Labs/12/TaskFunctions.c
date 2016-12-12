//
// Created by lieroz on 05.12.16.
//

#include "TaskFunctions.h"

bool find(const xmlChar* key, xmlChar** array, size_t size) {
	for (size_t i = 0; i < size; ++i) {

		if (!xmlStrcmp(key, array[i])) {
			return true;
		}
	}

	return false;
}

size_t get_city_index(const xmlChar* city, xmlChar** cities, size_t size) {
	for (size_t i = 0; i < size; ++i) {

		if (!xmlStrcmp(city, cities[i])) {
			return i;
		}
	}
}

void GetCityLocalizedSuppliers() {
	xmlDoc* file = xmlReadFile("Examples/XML_Suppliers.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	xmlNode*** nodes = (xmlNode***) malloc(sizeof(xmlNode**) * 256);

	for (size_t i = 0; i < 256; ++i) {
		nodes[i] = (xmlNode**) malloc(sizeof(xmlNode*) * 20);
	}

	size_t* cities_count = (size_t*) malloc(sizeof(size_t) * 256);
	xmlChar** cities = (xmlChar**) malloc(sizeof(xmlChar*) * 256);
	xmlChar* city_name = NULL;
	size_t count = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "City")) {
				city_name = xmlNodeListGetString(file, j->children, 1);

				if (!find(city_name, cities, count)) {
					cities_count[count] = 1;
					nodes[count][0] = i;
					cities[count++] = city_name;
				} else {
					nodes[get_city_index(city_name, cities, count)][cities_count[get_city_index(city_name,
					                                                                            cities,
					                                                                            count)]++] = i;
				}
			}
		}
	}

	for (size_t i = 0; i < count; ++i) {

		fprintf(stdout, BOLD(RED("%s: ")), cities[i]);

		for (size_t j = 0; j < cities_count[i]; ++j) {

			for (xmlNode* current = nodes[i][j]->children; current; current = current->next) {

				if (!xmlStrcmp(current->name, BAD_CAST "SupplierName")) {
					xmlChar* content = xmlNodeListGetString(file, current->children, 1);
					fprintf(stdout, BOLD(GREEN("%s ")) BOLD(CYAN("| ")), content);
				}
			}
		}

		fprintf(stdout, "\n");
	}

	for (size_t i = 0; i < count; ++i) {
		xmlFree(cities[i]);
	}

	free(cities_count);
	xmlFree(cities);
	xmlFree(city_name);
	xmlFree(root);
	xmlFree(file);
}
// ---------------------------------------------------------------------------------------------------------------------

void GetAllEngagedSuppliers() {
	xmlDoc* file = xmlReadFile("Examples/XML_Shipments.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	xmlChar** suppliers = (xmlChar**) malloc(sizeof(xmlChar*) * 256);
	xmlChar* supplier_id = NULL;
	size_t count = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "SupplierID")) {
				supplier_id = xmlNodeListGetString(file, j->children, 1);

				if (!find(supplier_id, suppliers, count)) {
					suppliers[count++] = supplier_id;
				}
			}
		}
	}

	fprintf(stdout, BOLD(YELLOW("Engaged SupplierID's: ")));

	for (size_t i = 0; i < count; ++i) {
		fprintf(stdout, BOLD(MAGENTA("%s | ")), suppliers[i]);
	}

	fprintf(stdout, BOLD(YELLOW("\nAmount of all suppliers engaged: ")) BOLD(MAGENTA("%lu\n")), count);

	xmlFree(suppliers);
	xmlFree(supplier_id);
	xmlFree(root);
	xmlFree(file);
}
// ---------------------------------------------------------------------------------------------------------------------

double GetProductPrice(int product_id) {
	xmlDoc* file = xmlReadFile("Examples/XML_Products.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	xmlChar* temp = NULL;
	int compared_key = 0;
	double result = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "ProductID")) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == product_id) {

					while (j->next && xmlStrcmp(j->name, BAD_CAST "Price")) {
						j = j->next;
					}

					if (!xmlStrcmp(j->name, BAD_CAST "Price")) {
						temp = xmlNodeListGetString(file, j->children, 1);
						sscanf((const char*) temp, "%lf", &result);
					}
					goto END;
				}
			}
		}
	}

	END:
	xmlFree(temp);
	xmlFree(root);
	xmlFree(file);

	return result;
}

void GetTotalProductCostBySupplier(int supplier_id) {
	xmlDoc* file = xmlReadFile("Examples/XML_Shipments.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	xmlChar* temp = NULL;

	if (!SearchForPrimaryKey(supplier_id, "Examples/XML_Suppliers.xml", "SupplierID")) {
		fprintf(stderr, "ERROR: NO SUCH SUPPLIER!");
		goto END;
	}

	int compared_key = 0;
	double result = 0;
	int product_id = 0;
	int quantity = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "SupplierID")) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == supplier_id) {
					j = j->next;
					temp = xmlNodeListGetString(file, j->children, 1);
					sscanf((const char*) temp, "%d", &product_id);

					j = j->next;
					temp = xmlNodeListGetString(file, j->children, 1);
					sscanf((const char*) temp, "%d", &quantity);

					result += GetProductPrice(product_id) * quantity;
				}
			}
		}
	}

	FPRINTF(BOLD(MAGENTA("Total products shipped by SupplierID{%d} cost: "))
		        BOLD(BLUE("%lf")), supplier_id, result);

	END:
	xmlFree(temp);
	xmlFree(root);
	xmlFree(file);
}
// ---------------------------------------------------------------------------------------------------------------------

bool find_id(int id, int* array_id, size_t size) {
	for (size_t i = 0; i < size; ++i) {

		if (id == array_id[i]) {
			return true;
		}
	}

	return false;
}

size_t get_id_index(int id, int* array_id, size_t size) {
	for (size_t i = 0; i < size; ++i) {

		if (id == array_id[i]) {
			return i;
		}
	}
}

void GetAllSuppliersTotalProductsQuantity() {
	xmlDoc* file = xmlReadFile("Examples/XML_Shipments.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	int* suppliers_id = (int*) malloc(sizeof(int) * 128);
	int* products_quantity = (int*) malloc(sizeof(int) * 128);
	size_t count = 0;
	xmlChar* temp = NULL;
	int supplier_id = 0;
	int qty = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "SupplierID")) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &supplier_id);
				j = j->next->next;

				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &qty);

				if (!find_id(supplier_id, suppliers_id, count)) {
					products_quantity[count] = qty;
					suppliers_id[count++] = supplier_id;
				} else {
					products_quantity[get_id_index(supplier_id, suppliers_id, count)] += qty;
				}
			}
		}
	}

	xmlFree(root);
	xmlFree(file);

	file = xmlReadFile("Examples/XML_Suppliers.xml", NULL, 0);
	root = xmlDocGetRootElement(file);

	fprintf(stdout, GREEN(BOLD("| SupplierID | Quantity |\n")));

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "SupplierID")) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &supplier_id);

				if (find_id(supplier_id, suppliers_id, count)) {
					qty = products_quantity[get_id_index(supplier_id, suppliers_id, count)];
				} else {
					qty = 0;
				}
			}
		}

		fprintf(stdout, BOLD(MAGENTA("| %*d | %*d |\n")),
		        (int) strlen("SupplierID"),
		        supplier_id,
		        (int) strlen("Quantity"),
		        qty);
	}

	xmlFree(temp);
	free(products_quantity);
	free(suppliers_id);
	xmlFree(root);
	xmlFree(file);
}
// ---------------------------------------------------------------------------------------------------------------------

void GetProductColor(int product_id) {
	xmlDoc* file = xmlReadFile("Examples/XML_Products.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	xmlChar* temp = NULL;
	int compared_key = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "ProductID")) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == product_id) {

					while (j->next && xmlStrcmp(j->name, BAD_CAST "Color")) {
						j = j->next;
					}

					if (!xmlStrcmp(j->name, BAD_CAST "Color")) {
						temp = xmlNodeListGetString(file, j->children, 1);
						fprintf(stdout, BOLD(BLUE("%s")) BOLD(MAGENTA(" | ")), temp);
					}

					goto END;
				}
			}
		}
	}

	END:
	xmlFree(temp);
	xmlFree(root);
	xmlFree(file);
}

void GetProductColorBySupplier(int supplier_id) {
	xmlDoc* file = xmlReadFile("Examples/XML_Shipments.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	xmlChar* temp = NULL;

	if (!SearchForPrimaryKey(supplier_id, "Examples/XML_Suppliers.xml", "SupplierID")) {
		fprintf(stderr, "ERROR: NO SUCH SUPPLIER!");
		goto END;
	}

	int compared_key = 0;
	int product_id = 0;

	fprintf(stdout, BOLD(MAGENTA("Product colors shipped by SupplierID{%d}: ")), supplier_id);

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "SupplierID")) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == supplier_id) {
					j = j->next;
					temp = xmlNodeListGetString(file, j->children, 1);
					sscanf((const char*) temp, "%d", &product_id);
					GetProductColor(product_id);
				}
			}
		}
	}

	fprintf(stdout, "\n");

	END:
	xmlFree(temp);
	xmlFree(root);
	xmlFree(file);
}
// ---------------------------------------------------------------------------------------------------------------------