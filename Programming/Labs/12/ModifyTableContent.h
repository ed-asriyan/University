//
// Created by lieroz on 05.12.16.
//

#ifndef LAB_12_MODIFYTABLECONTENT_H
#define LAB_12_MODIFYTABLECONTENT_H

#include "Helpers.h"

// Modifies content of suppliers table.
void ModifySupplier(const char* file_name, const char* tag_name, xmlDoc* file, xmlNode* root, int primary_key);

// Modifies content of products table.
void ModifyProduct(const char* file_name, const char* tag_name, xmlDoc* file, xmlNode* root, int primary_key);

// Modifies content of shipments table.
void ModifyShipment(const char* file_name, const char* tag_name, xmlDoc* file, xmlNode* root, int primary_key);

// Wrapper for 'Modifiers'.
void ModifyTableContent(const char* file_name,
                        const char* tag_name,
                        int primary_key,
                        void (* modify)(const char*, const char*, xmlDoc*, xmlNode*, int));

#endif //LAB_12_MODIFYTABLECONTENT_H
