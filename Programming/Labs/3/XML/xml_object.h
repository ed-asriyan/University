//
// Created by ed on 09.10.16.
//

#ifndef XMLCUSTOMERS_XMLOBJECT_H
#define XMLCUSTOMERS_XMLOBJECT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	char* tag_name;
	char* body;
} XmlObject;

XmlObject* ParseXml(char*, char** xml_end);

void FreeXmlObject(XmlObject*);

char* get_xml_object_tag_name(XmlObject*);

char* get_xml_object_body(XmlObject*);

#endif //XMLCUSTOMERS_XMLOBJECT_H
