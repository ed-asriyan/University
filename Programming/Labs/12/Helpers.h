//
// Created by lieroz on 04.12.16.
//

#ifndef LAB_12_HELPERS_H
#define LAB_12_HELPERS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <libxml/parser.h>

// Scans input text into buffer of characters preserving all symbols.
void ScanInput(char* buffer, size_t size, const char* name, bool is_null);

// Searches for primary key in tables, if key not fount returns false.
bool SearchForPrimaryKey(int primary_key, const char* file_name, const char* tag_name);

// Searches for unique pair {supplier_id, product_id} in XML_Shipments.xml file.
bool SearchForPair(int supplier_id, int product_id);

#endif //LAB_12_HELPERS_H