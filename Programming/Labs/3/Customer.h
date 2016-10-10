//
// Created by ed on 10.10.16.
//

#ifndef XMLCUSTOMERS_CUSTOMER_H
#define XMLCUSTOMERS_CUSTOMER_H

#include <stdlib.h>
#include <stdio.h>

#include "XML/xml_object.h"

typedef struct {
	int id;
	char* title;
	char* first_name;
	char* last_name;
	char* company_name;
	char* email_address;
	char* phone;
} Customer;

Customer* CreateCustomerFromXml(char*, char**);

void FreeCustomer(Customer*);

int get_customer_id(Customer*);

char* get_customer_first_name(Customer*);

char* get_customer_last_name(Customer*);

char* get_customer_company_name(Customer*);

char* get_customer_email_address(Customer*);

char* get_customer_phone(Customer*);

#endif //XMLCUSTOMERS_CUSTOMER_H
