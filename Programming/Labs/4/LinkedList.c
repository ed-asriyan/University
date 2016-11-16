#include "LinkedList.h"

List create_list() {
	List list;

	list.count = 0;
	list.head = list.tail = NULL;

	return list;
}

void add_last(List* list, Object* object) {
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

void remove_last(List* list) {
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

void add_first(List* list, Object* object) {
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

void remove_first(List* list) {
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

void insert_all(List* list, Object* object, int index) {
	if (index < 0 || index > list->count) {
		return;
	}

	if (index == 0) {
		add_first(list, object);
		return;
	}

	if (index == list->count) {
		add_last(list, object);
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

void remove_at(List* list, int index) {
	if (index < 0 || index > list->count - 1) {
		return;
	}

	if (index == 0) {
		remove_first(list);
		return;
	}

	if (index == list->count - 1) {
		remove_last(list);
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

void swap(struct Node* a, struct Node* b) {
	struct Node temp = *a;
	a->object = b->object;
	b->object = temp.object;
}

struct Node* partition(struct Node* left, struct Node* right, int (* cmp)(const void*, const void*)) {
	struct Node* i = left->prev;

	for (struct Node* j = left; j != right; j = j->next) {
		if (cmp(j, right) < 0) {
			i = (i == NULL) ? left : i->next;
			swap(i, j);
		}
	}

	i = (i == NULL) ? left : i->next;
	swap(i, right);
	return i;
}

void _quick_sort(struct Node* left, struct Node* right, int (* cmp)(const void*, const void*)) {
	if (right != NULL && left != right && left != right->next) {
		struct Node* p = partition(left, right, cmp);
		_quick_sort(left, p->prev, cmp);
		_quick_sort(p->next, right, cmp);
	}
}

void sort(List* list, int (* cmp)(const void*, const void*)) {
	_quick_sort(list->head, list->tail, cmp);
}

int int_comparator(const void* obj_1, const void* obj_2) {
	const struct Node* temp_obj_1 = (const struct Node*) obj_1;
	const struct Node* temp_obj_2 = (const struct Node*) obj_2;
	int result = temp_obj_1->object->employee_ID - temp_obj_2->object->employee_ID;

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
	double result = temp_obj_1->object->freight - temp_obj_2->object->freight;

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

	return strcmp(temp_obj_1->object->customer_ID, temp_obj_2->object->customer_ID);
}

void assign_values(Object* object, char* buffer, int index) {
	switch (index) {
		case 1: sscanf(buffer, "%d", &object->order_ID);
			free(buffer);
			break;
		case 2: object->customer_ID = buffer;
			break;
		case 3: sscanf(buffer, "%d", &object->employee_ID);
			free(buffer);
			break;
		case 4: object->order_date = buffer;
			break;
		case 5: object->required_date = buffer;
			break;
		case 6: object->shipped_date = buffer;
			break;
		case 7: sscanf(buffer, "%lf", &object->freight);
			free(buffer);
			break;
	}
}

bool is_separator(char symbol) {
	if (symbol == ' ' || symbol == '\n' || symbol == EOF) {
		return true;
	}

	return false;
}

void to_list(List* list, FILE* f) {
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
		} else if (is_separator(symbol)) {
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

			assign_values(object, buffer, i);
			if (i == 7) {
				add_last(list, object);
				i = 0;
				object = (Object*) malloc(sizeof(Object));
			}

			fseek(f, current_index, SEEK_SET);
		}
	}
}

void to_file(List* list, FILE* f) {
	struct Node* current = list->head;
	while (current != NULL) {
		fprintf(f, "%d\n", current->object->order_ID);
		fprintf(f, "%s\n", current->object->customer_ID);
		fprintf(f, "%d\n", current->object->employee_ID);
		fprintf(f, "%s\n", current->object->order_date);
		fprintf(f, "%s\n", current->object->required_date);
		fprintf(f, "%s\n", current->object->shipped_date);
		fprintf(f, "%lf\n\n", current->object->freight);
		current = current->next;
	}
}

bool is_empty(List* list) {
	return list->count == 0;
}

int length(List* list) {
	return list->count;
}

void reverse(List* list) {
	struct Node* h_curr = list->head;
	struct Node* t_curr = list->tail;
	int size = list->count / 2;

	for (int i = 0; i < size; ++i) {
		swap(h_curr, t_curr);

		h_curr = h_curr->next;
		t_curr = t_curr->prev;
	}
}

void print(const List* list) {
	struct Node* current = list->head;
	while (current != NULL) {
		fprintf(stdout, "%d\n", current->object->order_ID);
		fprintf(stdout, "%s\n", current->object->customer_ID);
		fprintf(stdout, "%d\n", current->object->employee_ID);
		fprintf(stdout, "%s\n", current->object->order_date);
		fprintf(stdout, "%s\n", current->object->required_date);
		fprintf(stdout, "%s\n", current->object->shipped_date);
		fprintf(stdout, "%lf\n\n", current->object->freight);
		current = current->next;
	}
}

void clear(List* list) {
	if (is_empty(list)) {
		return;
	}

	struct Node* current = list->head;
	while (current) {
		struct Node* next = current->next;
		free(current->object->customer_ID);
		free(current->object->order_date);
		free(current->object->required_date);
		free(current->object->shipped_date);
		free(current->object);
		free(current);
		current = next;
	}

	list->head = list->tail = 0;
}