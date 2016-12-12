//
// Created by lieroz on 04.12.16.
//

#ifndef LAB_12_ADDTOFILE_H
#define LAB_12_ADDTOFILE_H

#include "Helpers.h"

// Adds content into XML_Suppliers.xml.
void AddSupplier(const char* file_name, xmlDoc* file, xmlNode* root);

// Adds content into XML_Products.xml.
void AddProduct(const char* file_name, xmlDoc* file, xmlNode* root);

// Adds content into XML_Shipments.xml.
void AddShipment(const char* file_name, xmlDoc* file, xmlNode* root);

// Wrapper for 'Adders'.
void AddToFile(const char* file_name, void (* add)(const char*, xmlDoc*, xmlNode*));

#endif //LAB_12_ADDTOFILE_H
