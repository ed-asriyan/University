#include "LinkedList.h"

List Constructor() {
	List list;

	list.count = 0;
	list.head = list.tail = NULL;

	return list;
}

// Public methods
// Adding element to the end of list
void AddLast(List* list, Object* object) {
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));

	node->object = object;

	if (list->tail) {
		list->tail->next = node;
	}

	node->next = NULL;
	node->prev = list->tail;
	list->tail = node;

	if (list->head == NULL) {
		list->head = node;
	}

	++list->count;
}

//-------------------------------------------------------------------------------------------------
// Removing element from the end of list
void RemoveLast(List* list) {
	if (list->head == NULL) {
		return;
	}

	struct Node* temp = list->tail->prev;

	if (list->head != list->tail) {
		temp->next = NULL;
	}

	free(list->tail->object);
	free(list->tail);

	if (list->head != list->tail) {
		list->tail = temp;
	} else {
		list->head = list->tail = NULL;
	}

	--list->count;
}

//-------------------------------------------------------------------------------------------------
// Add element to the beginning of list
void AddFirst(List* list, Object* object) {
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));

	node->object = object;

	if (list->head) {
		list->head->prev = node;
	}

	node->prev = NULL;
	node->next = list->head;
	list->head = node;

	if (list->tail == NULL) {
		list->tail = node;
	}

	++list->count;
}

//-------------------------------------------------------------------------------------------------
// Remove element from the beginning of list
void RemoveFirst(List* list) {
	if (list->head == NULL) {
		return;
	}

	struct Node* temp = list->head->next;

	if (list->head != list->tail) {
		temp->prev = NULL;
	}

	free(list->head->object);
	free(list->head);

	if (list->head != list->tail) {
		list->head = temp;
	} else {
		list->head = list->tail = NULL;
	}

	--list->count;
}

//-------------------------------------------------------------------------------------------------
// Insert element into list by index
void InsertAt(List* list, Object* object, int index) {
	if (index < 0 || index > list->count) {
		return;
	}

	if (index == 0) {
		AddFirst(list, object);
		return;
	}

	if (index == list->count) {
		AddLast(list, object);
		return;
	}

	struct Node* current = list->head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}

	struct Node* node = (struct Node*) malloc(sizeof(struct Node));

	node->object = object;

	node->next = current;
	node->prev = current->prev;
	current->prev->next = node;
	current->prev = node;
}

//-------------------------------------------------------------------------------------------------
// Remove element from list by index
void RemoveAt(List* list, int index) {
	if (index < 0 || index > list->count - 1) {
		return;
	}

	if (index == 0) {
		RemoveFirst(list);
		return;
	}

	if (index == list->count - 1) {
		RemoveLast(list);
		return;
	}

	struct Node* current = list->head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}

	current->next->prev = current->prev;
	current->prev->next = current->next;

	free(current->object);
	free(current);
}

//-------------------------------------------------------------------------------------------------
// Quicksort for doubly-linked list
void Swap(struct Node* a, struct Node* b) {
	struct Node temp = *a;
	a->object = b->object;
	b->object = temp.object;
}

struct Node* Partition(struct Node* left, struct Node* right, int (* cmp)(const void*, const void*)) {
	struct Node* i = left->prev;

	for (struct Node* j = left; j != right; j = j->next) {
		if (cmp(j, right) < 0) {
			i = (i == NULL) ? left : i->next;
			Swap(i, j);
		}
	}

	i = (i == NULL) ? left : i->next;
	Swap(i, right);
	return i;
}

void _QuickSort(struct Node* left, struct Node* right, int (* cmp)(const void*, const void*)) {
	if (right != NULL && left != right && left != right->next) {
		struct Node* p = Partition(left, right, cmp);
		_QuickSort(left, p->prev, cmp);
		_QuickSort(p->next, right, cmp);
	}
}

void Sort(List* list, int (* cmp)(const void*, const void*)) {
	_QuickSort(list->head, list->tail, cmp);
}

// Comparators for sorting
int int_comparator(const void* obj_1, const void* obj_2) {
	const struct Node* temp_obj_1 = (const struct Node*) obj_1;
	const struct Node* temp_obj_2 = (const struct Node*) obj_2;
	int result = temp_obj_1->object->OBJECT_FEATURE_3 - temp_obj_2->object->OBJECT_FEATURE_3;

	if (result < 0) {
		return -1;
	} else if (result > 0) {
		return 1;
	}

	return 0;
}

int double_comparator(const void* obj_1, const void* obj_2) {
	const struct Node* temp_obj_1 = (const struct Node*) obj_1;
	const struct Node* temp_obj_2 = (const struct Node*) obj_2;
	double result = temp_obj_1->object->OBJECT_FEATURE_7 - temp_obj_2->object->OBJECT_FEATURE_7;

	if (result < 0) {
		return -1;
	} else if (result > 0) {
		return 1;
	}

	return 0;
}

int string_comparator(const void* obj_1, const void* obj_2) {
	const struct Node* temp_obj_1 = (const struct Node*) obj_1;
	const struct Node* temp_obj_2 = (const struct Node*) obj_2;

	return strcmp(temp_obj_1->object->OBJECT_FEATURE_2, temp_obj_2->object->OBJECT_FEATURE_2);
}

//-------------------------------------------------------------------------------------------------
// Get file info into list
void AssignValues(Object* object, char* buffer, int index) {
	switch (index) {
		case 1: sscanf(buffer, "%d", &object->OBJECT_FEATURE_1);
			free(buffer);
			break;
		case 2: object->OBJECT_FEATURE_2 = buffer;
			break;
		case 3: sscanf(buffer, "%d", &object->OBJECT_FEATURE_3);
			free(buffer);
			break;
		case 4: object->OBJECT_FEATURE_4 = buffer;
			break;
		case 5: object->OBJECT_FEATURE_5 = buffer;
			break;
		case 6: object->OBJECT_FEATURE_6 = buffer;
			break;
		case 7: sscanf(buffer, "%lf", &object->OBJECT_FEATURE_7);
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

void ToList(List* list, FILE* f) {
	list->count = 0;
	list->head = list->tail = 0;

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
		} else if (IsSeparator(symbol)) {
			continue;
		} else {
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
				AddLast(list, object);
				i = 0;
				object = (Object*) malloc(sizeof(Object));
			}

			fseek(f, current_index, SEEK_SET);
		}
	}
}

//-------------------------------------------------------------------------------------------------
// Prints list info into file
void ToFile(List* list, FILE* f) {
	struct Node* current = list->head;
	while (current != NULL) {
		fprintf(f, "%d\n", current->object->OBJECT_FEATURE_1);
		fprintf(f, "%s\n", current->object->OBJECT_FEATURE_2);
		fprintf(f, "%d\n", current->object->OBJECT_FEATURE_3);
		fprintf(f, "%s\n", current->object->OBJECT_FEATURE_4);
		fprintf(f, "%s\n", current->object->OBJECT_FEATURE_5);
		fprintf(f, "%s\n", current->object->OBJECT_FEATURE_6);
		fprintf(f, "%lf\n\n", current->object->OBJECT_FEATURE_7);
		current = current->next;
	}
}

//-------------------------------------------------------------------------------------------------
bool IsEmpty(List* list) {
	return list->count == 0;
}

int Length(List* list) {
	return list->count;
}

//-------------------------------------------------------------------------------------------------
// Reversing the list
void Reverse(List* list) {
	struct Node* h_curr = list->head;
	struct Node* t_curr = list->tail;
	int size = list->count / 2;

	for (int i = 0; i < size; ++i) {
		Swap(h_curr, t_curr);

		h_curr = h_curr->next;
		t_curr = t_curr->prev;
	}
}

//-------------------------------------------------------------------------------------------------
// Print list elements to stdout
void Print(const List* list) {
	struct Node* current = list->head;
	while (current != NULL) {
		fprintf(stdout, "%d\n", current->object->OBJECT_FEATURE_1);
		fprintf(stdout, "%s\n", current->object->OBJECT_FEATURE_2);
		fprintf(stdout, "%d\n", current->object->OBJECT_FEATURE_3);
		fprintf(stdout, "%s\n", current->object->OBJECT_FEATURE_4);
		fprintf(stdout, "%s\n", current->object->OBJECT_FEATURE_5);
		fprintf(stdout, "%s\n", current->object->OBJECT_FEATURE_6);
		fprintf(stdout, "%lf\n\n", current->object->OBJECT_FEATURE_7);
		current = current->next;
	}
}

//-------------------------------------------------------------------------------------------------
// Delete list
void Clear(List* list) {
	if (IsEmpty(list)) {
		return;
	}

	struct Node* current = list->head;
	while (current) {
		struct Node* next = current->next;
		free(current->object->OBJECT_FEATURE_2);
		free(current->object->OBJECT_FEATURE_4);
		free(current->object->OBJECT_FEATURE_5);
		free(current->object->OBJECT_FEATURE_6);
		free(current->object);
		free(current);
		current = next;
	}

	list->head = list->tail = 0;
}