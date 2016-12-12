//
// Created by lieroz on 04.12.16.
//

#include "AddToFile.h"

void AddSupplier(const char* file_name, xmlDoc* file, xmlNode* root) {
	xmlNode* current = root->children;

	while (current->next != NULL) {
		current = current->next;
	}

	xmlNode* new_node = xmlNewChild(root, 0, BAD_CAST "Supplier", 0);
	xmlChar* table_child = xmlNodeListGetString(file, current->children->children, 1);
	size_t size = 256;
	char* buffer = malloc(sizeof(char) * size);
	int supplier_id = 0;

	sscanf((const char*) table_child, "%d", &supplier_id);
	sprintf(buffer, "%d", ++supplier_id);
	xmlNewChild(new_node, 0, BAD_CAST "SupplierID", BAD_CAST buffer);

	ScanInput(buffer, size, "SupplierName", false);
	xmlNewChild(new_node, 0, BAD_CAST "SupplierName", BAD_CAST buffer);

	ScanInput(buffer, size, "Status", false);
	int status = 0;

	while (sscanf(buffer, "%d", &status) != 1 || (status < 0 || status > 100)) {
		ScanInput(buffer, size, "Status", false);
	}

	sprintf(buffer, "%d", status);
	xmlNewChild(new_node, 0, BAD_CAST "Status", BAD_CAST buffer);

	ScanInput(buffer, size, "City", false);
	xmlNewChild(new_node, 0, BAD_CAST "City", BAD_CAST buffer);

	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);

	free(buffer);
	xmlFree(table_child);
	xmlFree(new_node);
	xmlFree(current);
}

void AddProduct(const char* file_name, xmlDoc* file, xmlNode* root) {
	xmlNode* current = root->children;

	while (current->next != NULL) {
		current = current->next;
	}

	xmlNode* new_node = xmlNewChild(root, 0, BAD_CAST "Product", 0);
	xmlChar* table_child = xmlNodeListGetString(file, current->children->children, 1);
	size_t size = 256;
	char* buffer = malloc(sizeof(char) * size);
	int product_id = 0;

	sscanf((const char*) table_child, "%d", &product_id);
	sprintf((char*) table_child, "%d", ++product_id);
	xmlNewChild(new_node, 0, BAD_CAST "ProductID", table_child);

	ScanInput(buffer, size, "ProductName", false);
	xmlNewChild(new_node, 0, BAD_CAST "ProductName", BAD_CAST buffer);

	ScanInput(buffer, size, "Color", true);

	if (strlen(buffer) != 0) {
		xmlNewChild(new_node, 0, BAD_CAST "Color", BAD_CAST buffer);
	}

	ScanInput(buffer, size, "Weight", true);
	double weight = 0;

	if (strlen(buffer) != 0) {

		while (sscanf(buffer, "%lf", &weight) != 1 || weight <= 0) {
			ScanInput(buffer, size, "Weight", true);

			if (strlen(buffer) == 0) {
				break;
			}
		}

		sprintf(buffer, "%.2lf", weight);
		xmlNewChild(new_node, 0, BAD_CAST "Weight", BAD_CAST buffer);
	}

	ScanInput(buffer, size, "Price", true);
	double price = 0;

	if (strlen(buffer) != 0) {

		while (sscanf(buffer, "%lf", &price) != 1 || price < 0) {
			ScanInput(buffer, size, "Price", true);

			if (strlen(buffer) == 0) {
				break;
			}
		}

		sprintf(buffer, "%.2lf", price);
		xmlNewChild(new_node, 0, BAD_CAST "Price", BAD_CAST buffer);
	}

	ScanInput(buffer, size, "City", false);
	xmlNewChild(new_node, 0, BAD_CAST "City", BAD_CAST buffer);

	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);

	free(buffer);
	xmlFree(table_child);
	xmlFree(new_node);
	xmlFree(current);
}

void AddShipment(const char* file_name, xmlDoc* file, xmlNode* root) {
	xmlNode* current = root->children;

	while (current->next != NULL) {
		current = current->next;
	}

	xmlNode* new_node = xmlNewChild(root, 0, BAD_CAST "Shipment", 0);
	xmlChar* table_child = xmlNodeListGetString(file, current->children->children, 1);
	size_t size = 256;
	char* buffer = malloc(sizeof(char) * size);
	int shipment_id = 0;

	sscanf((const char*) table_child, "%d", &shipment_id);
	sprintf((char*) table_child, "%d", ++shipment_id);
	xmlNewChild(new_node, 0, BAD_CAST "ShipmentID", table_child);

	ScanInput(buffer, size, "SupplierID", false);
	int supplier_id = 0;

	while (sscanf(buffer, "%d", &supplier_id) != 1
		|| !SearchForPrimaryKey(supplier_id, "Examples/XML_Suppliers.xml", "SupplierID")) {
		ScanInput(buffer, size, "SupplierID", false);
	}

	sprintf(buffer, "%d", supplier_id);
	xmlNewChild(new_node, 0, BAD_CAST "SupplierID", BAD_CAST buffer);

	ScanInput(buffer, size, "ProductID", false);
	int product_id = 0;

	while (sscanf(buffer, "%d", &product_id) != 1
		|| !SearchForPrimaryKey(product_id, "Examples/XML_Products.xml", "ProductID")
		|| SearchForPair(supplier_id, product_id)) {
		ScanInput(buffer, size, "ProductID", false);
	}

	sprintf(buffer, "%d", product_id);
	xmlNewChild(new_node, 0, BAD_CAST "ProductID", BAD_CAST buffer);

	ScanInput(buffer, size, "Qty", false);
	int qty = 0;

	while (sscanf(buffer, "%d", &qty) != 1 || qty <= 0) {
		ScanInput(buffer, size, "Qty", false);
	}

	sprintf(buffer, "%d", qty);
	xmlNewChild(new_node, 0, BAD_CAST "Qty", BAD_CAST buffer);

	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);

	free(buffer);
	xmlFree(table_child);
	xmlFree(new_node);
	xmlFree(current);
}

void AddToFile(const char* file_name, void (* add)(const char*, xmlDoc*, xmlNode*)) {
	xmlDoc* file = xmlReadFile(file_name, NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);

	add(file_name, file, root);
//	add(NULL, file, root);

	xmlFree(root);
	xmlFree(file);
}