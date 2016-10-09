//
// Created by ed on 09.10.16.
//

#include "xml_object.h"

XmlObject* ParseXml(char* str, char** xml_end) {
	// searching the beginning of the xml
	while (*str != '<') {
		// if xml object is invalid
		if (*str != ' ' &&
			*str != '\n' &&
			*str != '\r') {
			return NULL;
		}

		++str;
	}

	char* open_tag_beginning = str;
	char* open_tag_ending = strchr(str, '>') + 1;
	long open_tag_len = (long) (open_tag_ending - open_tag_beginning);

	// if there are not open tag ending, xml is invalid
	if (open_tag_ending == NULL) {
		return NULL;
	}

	char* open_tag = (char*) malloc(sizeof(char) * (open_tag_len + 1));
	memcpy(open_tag, open_tag_beginning, sizeof(char) * open_tag_len);
	open_tag[open_tag_len] = '\0';

	// creating close tag protohype (for searching substr in source str)
	long close_tag_len = open_tag_len + 1;
	char* close_tag = (char*) malloc(sizeof(char) * (close_tag_len + 1));
	memcpy(close_tag + 2, open_tag + 1, sizeof(char) * (close_tag_len - 2));
	close_tag[close_tag_len] = '\0';
	close_tag[0] = '<';
	close_tag[1] = '/';

	XmlObject* result = NULL;

	char* close_tag_beginning = strstr(str, close_tag);

	// if closing tag is not found
	if (close_tag_beginning != NULL) {
		result = (XmlObject*) malloc(sizeof(XmlObject));

		// filling tag_name (copying from open_tag)
		result->tag_name = (char*) malloc(sizeof(char) * (open_tag_len - 1));
		memcpy(result->tag_name, open_tag_beginning + 1, sizeof(char) * (open_tag_len - 2));
		result->tag_name[open_tag_len - 2] = '\0';

		// filling body
		long body_len = (long) (close_tag_beginning - open_tag_ending);
		result->body = (char*) malloc(sizeof(char) * (body_len + 1));
		memcpy(result->body, open_tag_ending, sizeof(char) * body_len);
		result->body[body_len] = '\0';
	}

	free(close_tag);
	free(open_tag);

	if (xml_end != NULL) {
		*xml_end = close_tag_beginning + close_tag_len;
	}

	return result;
}

void freeXmlObject(XmlObject* obj) {
	free(obj->tag_name);
	free(obj->body);
	free(obj);
}

char* get_xml_object_tag_name(XmlObject* obj) {
	return obj->tag_name;
}

char* get_xml_object_body(XmlObject* obj) {
	return obj->body;
}
