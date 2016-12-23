//
// Created by lieroz on 04.12.16.
//

#include "PrintTable.h"

void PrintSuppliers(xmlDoc* file, xmlNode* root) {
	xmlChar* content = NULL;

	for (xmlNode* current = root->children; current; current = current->next) {

		if ((!xmlStrcmp(current->name, BAD_CAST "SupplierID"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "SupplierID: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "SupplierName"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "SupplierName: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "Status"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "Status: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "City"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "City: " "%s" "\n", content);
		}
	}

	xmlFree(content);
}

void PrintProducts(xmlDoc* file, xmlNode* root) {
	xmlChar* content = NULL;

	for (xmlNode* current = root->children; current; current = current->next) {

		if ((!xmlStrcmp(current->name, BAD_CAST "ProductID"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "ProductID: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "ProductName"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "ProductName: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "Color"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "Color: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "Weight"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "Weight: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "Price"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "Price: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "City"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "City: " "%s" "\n", content);
		}
	}

	xmlFree(content);
}

void PrintShipments(xmlDoc* file, xmlNode* root) {
	xmlChar* content = NULL;

	for (xmlNodePtr current = root->children; current; current = current->next) {

		if ((!xmlStrcmp(current->name, BAD_CAST "ShipmentID"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "ShipmentID: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "SupplierID"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "SupplierID: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "ProductID"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "ProductID: " "%s" "\n", content);
		} else if ((!xmlStrcmp(current->name, BAD_CAST "Qty"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			fprintf(stdout, "Qty: " "%s" "\n", content);
		}
	}

	xmlFree(content);
}

void PrintTable(const char* file_name, void (* print)(xmlDoc*, xmlNode*)) {
	xmlDoc* file = xmlReadFile(file_name, NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);

	for (xmlNode* current = root->children; current; current = current->next) {
		print(file, current);
		fprintf(stdout, "\n");
	}

	xmlFree(file);
	xmlFree(root);
}