#ifndef __LIST__H__
#define __LIST__H__

#include <stdlib.h>
#include <assert.h>

#include "student.h"

typedef student_t list_item_t;

struct Node
{
    struct Node* next;
    struct Node* prev;

    list_item_t value;
};

typedef struct Node node_t;

struct List
{
    struct Node* head;
    struct Node* tail;

    unsigned int count;
};

typedef struct List list_t;

list_t* list_create();

void list_free(list_t* list);

node_t* list_insert(list_t* list, node_t* insert_after, list_item_t value);

node_t* list_push_back(list_t* list, list_item_t value);

node_t* list_remove(list_t* list, node_t* node);

#endif

