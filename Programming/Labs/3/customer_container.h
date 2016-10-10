//
// Created by ed on 10.10.16.
//

#ifndef XMLCUSTOMERS_CUSTOMERCONTAINER_H
#define XMLCUSTOMERS_CUSTOMERCONTAINER_H

#include <stdlib.h>

#include "XML/xml_object.h"
#include "customer.h"

int ReadWholeCustomerList(XmlObject* root, Customer*** result);

void FreeCustomerList(Customer** c, int count);

void MergeSort(Customer** array, int count, int (*cmp)(Customer* a, Customer* b));

#endif //XMLCUSTOMERS_CUSTOMERCONTAINER_H
