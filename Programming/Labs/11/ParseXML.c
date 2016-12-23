#include "ParseXML.h"

// Parser part
void AssignValues(Object* object, char* buffer, int index) {
	switch (index) {
		case 1:
			sscanf(buffer, "%d", &object->OBJECT_FEATURE_1);
			free(buffer);
			break;
		case 2:
			object->OBJECT_FEATURE_2 = buffer;
			break;
		case 3:
			sscanf(buffer, "%d", &object->OBJECT_FEATURE_3);
			free(buffer);
			break;
		case 4:
			object->OBJECT_FEATURE_4 = buffer;
			break;
		case 5:
			object->OBJECT_FEATURE_5 = buffer;
			break;
		case 6:
			object->OBJECT_FEATURE_6 = buffer;
			break;
		case 7:
			sscanf(buffer, "%lf", &object->OBJECT_FEATURE_7);
			free(buffer);
			break;
	}
}

bool IsSeparator(char symbol) {
	if (symbol == ' ' || symbol == '\n' || symbol == EOF) {
		return true;
	}

	return false;
}

BSTNode* FillTree(FILE* f) {
	BSTNode* root = NULL;

	Object* object = (Object*) malloc(sizeof(Object));

	int current_index = 0;
	int onset = 0;
	int i = 0;

	while (!feof(f)) {
		++current_index;
		char symbol = fgetc(f);

		if (symbol == '<') {

			while (symbol != '>') {
				++current_index;
				symbol = fgetc(f);
			}

			continue;
		}

		else if (IsSeparator(symbol)) {
			continue;
		}

		else {
			++i;
			fseek(f, --current_index, SEEK_SET);
			onset = current_index;

			while (true) {
				symbol = fgetc(f);
				if (symbol == '<') {
					break;
				}
				++current_index;
			}

			fseek(f, onset, SEEK_SET);

			int element_length = current_index - onset;
			char* buffer = (char*) malloc(sizeof(char) * (element_length + 1));

			for (int i = 0; i < element_length; ++i) {
				buffer[i] = fgetc(f);
			}

			buffer[element_length] = '\0';
			AssignValues(object, buffer, i);

			if (i == OBJECT_FEATURE_COUNT) {
				root = Insert(root, object);
				i = 0;
				object = (Object*) malloc(sizeof(Object));
			}

			fseek(f, current_index, SEEK_SET);
		}
	}

	return root;
}