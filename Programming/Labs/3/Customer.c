//
// Created by ed on 10.10.16.
//

#include "Customer.h"

Customer* CreateCustomerFromXml(char* str, char** xml_end) {
	XmlObject* xml = ParseXml(str, xml_end);
	if (xml == NULL) {
		fprintf(stderr, "Error parsing customer xml object\n");
		return NULL;
	}

	Customer* result = NULL;

	// if it is not a customer object
	if (strcmp(get_xml_object_tag_name(xml), "Customer")) {
		fprintf(stderr, "Not a xml customer object\n");
	} else {
		char* customer_id = "-1";
		char* customer_title = "";
		char* customer_first_name = "";
		char* customer_last_name = "";
		char* customer_company_name = "";
		char* customer_email_address = "";
		char* customer_phone = "";

		char* properties_str = get_xml_object_body(xml);
		char* properties_str_end = properties_str + (long) strlen(properties_str);

		// reading all properties
		while (properties_str != properties_str_end) {
			char** property_addr = NULL;

			// parsing xml property
			XmlObject* property = ParseXml(properties_str, &properties_str);
			if (property == NULL) {
				fprintf(stderr, "Error parsing customer property\n");
				break;
			}

			// detecting property name
			if (!strcmp("CustomerID", get_xml_object_tag_name(property))) {
				property_addr = &customer_id;
			} else if (!strcmp("Title", get_xml_object_tag_name(property))) {
				property_addr = &customer_title;
			} else if (!strcmp("FirstName", get_xml_object_tag_name(property))) {
				property_addr = &customer_first_name;
			} else if (!strcmp("LastName", get_xml_object_tag_name(property))) {
				property_addr = &customer_last_name;
			} else if (!strcmp("CompanyName", get_xml_object_tag_name(property))) {
				property_addr = &customer_company_name;
			} else if (!strcmp("EmailAddress", get_xml_object_tag_name(property))) {
				property_addr = &customer_email_address;
			} else if (!strcmp("Phone", get_xml_object_tag_name(property))) {
				property_addr = &customer_phone;
			}

			// saving property
			if (property_addr != NULL) {
				char* property_value = get_xml_object_body(property);
				long property_len = (long) strlen(property_value);

				*property_addr = (char*) malloc(sizeof(char) * (property_len + 1));
				memcpy(*property_addr, property_value, sizeof(char) * property_len);
				(*property_addr)[property_len] = '\0';
			}

			// free temp xml object
			FreeXmlObject(property);
		}

		// if not all properties are exist
		if (customer_id == NULL ||
			customer_title == NULL ||
			customer_first_name == NULL ||
			customer_last_name == NULL ||
			customer_company_name == NULL ||
			customer_email_address == NULL ||
			customer_phone == NULL) {
			fprintf(stderr, "Not all customer properties are exist\n");
		} else {
			result = (Customer*) malloc(sizeof(Customer));
			result->id = atoi(customer_id);
			result->title = customer_title;
			result->first_name = customer_first_name;
			result->last_name = customer_last_name;
			result->company_name = customer_company_name;
			result->email_address = customer_email_address;
			result->phone = customer_phone;
		}

		FreeXmlObject(xml);
	}

	return result;
}

int get_customer_id(Customer* customer) {
	return customer->id;
}

char* get_customer_first_name(Customer* customer) {
	return customer->first_name;
}

char* get_customer_last_name(Customer* customer) {
	return customer->last_name;
}

char* get_customer_company_name(Customer* customer) {
	return customer->company_name;
}

char* get_customer_email_address(Customer* customer) {
	return customer->email_address;
}

char* get_customer_phone(Customer* customer) {
	return customer->phone;
}

void FreeCustomer(Customer* customer) {
	free(customer->first_name);
	free(customer->last_name);
	free(customer->company_name);
	free(customer->email_address);
	free(customer->phone);
	free(customer);
}
