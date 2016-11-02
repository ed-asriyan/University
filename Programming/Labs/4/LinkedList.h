#ifndef LISTS_LINKEDLIST_H
#define LISTS_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Change this to change your object features.
// 	You will have to change lines 21 - 29 in Object.h,
// if you wanna another features of object.

// 	Also you will have to rebuild functions: PrintList (lines 23 - 35),
// FreeList (lines 37 - 51) & AssignValues (lines 53 - 80) in file Object.c.
#define OBJECT_FEATURE_COUNT 7

#define OBJECT_FEATURE_1      order_ID
#define OBJECT_FEATURE_2   customer_ID
#define OBJECT_FEATURE_3   employee_ID
#define OBJECT_FEATURE_4    order_date
#define OBJECT_FEATURE_5 required_date
#define OBJECT_FEATURE_6  shipped_date
#define OBJECT_FEATURE_7       freight

// Representation of object
typedef struct {
	int OBJECT_FEATURE_1;
	char* OBJECT_FEATURE_2;
	int OBJECT_FEATURE_3;
	char* OBJECT_FEATURE_4;
	char* OBJECT_FEATURE_5;
	char* OBJECT_FEATURE_6;
	double OBJECT_FEATURE_7;
} Object;

// Two-linked list to store data from file
// List node
struct Node {
	Object* object;

	struct Node* next;
	struct Node* prev;
};

// List head & tail
typedef struct {
	int count;

	struct Node* head;
	struct Node* tail;
} List;

// Public methods
List Constructor();

// Removing and adding elements
void AddLast(List*, Object*);
void RemoveLast(List*);
void AddFirst(List*, Object*);
void RemoveFirst(List*);

void InsertAt(List*, Object*, int);
void RemoveAt(List*, int);

// Sort list by comparator
void Sort(List*, int (* cmp)(const void*, const void*));
// Comparators for sorting
int int_comparator(const void*, const void*);
int double_comparator(const void*, const void*);
int string_comparator(const void*, const void*);

// Get file info into list
void ToList(List*, FILE*);
// Get list info into file
void ToFile(List*, FILE*);

// 'Cheap' functions
bool IsEmpty(List*);
int Length(List*);

// Reversing the list
void Reverse(List*);

// Print list elements to stdout

#endif //LISTS_LINKEDLIST_H
