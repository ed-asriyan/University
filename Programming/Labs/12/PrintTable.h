//
// Created by lieroz on 04.12.16.
//

#ifndef LAB_12_PRINTDOCS_H
#define LAB_12_PRINTDOCS_H

#include <libxml/parser.h>

#include "Colors.h"

void PrintSuppliers(xmlDoc* file, xmlNode* root);

void PrintProducts(xmlDoc* file, xmlNode* root);

void PrintShipments(xmlDoc* file, xmlNode* root);

void PrintTable(const char* file_name, void (* print)(xmlDoc*, xmlNode*));

#endif //LAB_12_PRINTDOCS_H
