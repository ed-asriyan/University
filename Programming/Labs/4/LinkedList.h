#ifndef LISTS_LINKEDLIST_H
#define LISTS_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Representation of object
 */
typedef struct {
	int order_ID;
	char* customer_ID;
	int employee_ID;
	char* order_date;
	char* required_date;
	char* shipped_date;
	double freight;
} Object;

/**
 * @brief List node
 */
struct Node {
	Object* object;

	struct Node* next;
	struct Node* prev;
};

/**
 * @brief Two-linked list to store data from file
 */
typedef struct {
	int count;

	struct Node* head;
	struct Node* tail;
} List;

/**
 * @brief Creates new list.
 */
List create_list();

/**
 * @brief Adds element to the end of the list.
 * @param list List, in which it is necessary to add an object.
 * @param object The object that it is necessary to add.
 */
void add_last(List* list, Object* object);

/**
 * @brief Removes the element from the end of the list.
 * @param list List, from which it is necessary to remove the last object.
 */
void remove_last(List* list);

/**
 * @brief Adds the element to the beginning of the list.
 * @param list List, in which it is necessary to add an object.
 * @param object The object that it is necessary to add.
 */
void add_first(List* list, Object* object);

/**
 * @brief Removes element from the beginning of list.
 * @param list List, from which it is necessary to remove the first object.
 */
void remove_first(List* list);

/**
 * @brief Inserts element into list by index.
 * @param list List, in which it is necessary to insert an object.
 * @param object The object that it is necessary to insert.
 * @param index The inserting object index.
 */
void insert_all(List* list, Object* object, int index);

/**
 * @brief Removes element from list by index
 * @param list List, from which it is necessary to remove the object.
 * @param index The removing object index.
 */
void remove_at(List* list, int index);

/**
 * @brief Sorts list by comparator.
 * @param cmp The comparator.
 */
void sort(List*, int (* cmp)(const void*, const void*));

int int_comparator(const void*, const void*);
int double_comparator(const void*, const void*);
int string_comparator(const void*, const void*);

/**
 * @brief Gets file info into list.
 */
void to_list(List*, FILE*);

/**
 * @brief Gets list info into file.
 */
void to_file(List*, FILE*);

// 'Cheap' functions
bool is_empty(List*);
int length(List*);

/**
 * @brief Reverses the list.
 */
void reverse(List*);

/**
 * @brief Prints list elements to stdout.
 * @param list The list, which it is necessary to print.
 */
void print(const List* list);

/**
 * @brief Clears the list
 * @param list The list, which it is necessary to clear.
 */
void clear(List* list);

#endif //LISTS_LINKEDLIST_H
