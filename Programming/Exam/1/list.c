#include "list.h"

list_t* list_create()
{
    list_t* result = (list_t*)malloc(sizeof(list_t));
    if (result == NULL) return NULL;

    result->head = NULL;
    result->tail = NULL;
    result->count = 0;

    return result;
}

void list_free(list_t* list)
{
    if (list == NULL) return;
    node_t* node = list->head;
    while (node != NULL)
    {
        node_t* node_next = node->next;
        free(node);
        node = node_next;
    }
    free(list);
}

node_t* list_insert(list_t* list, node_t* insert_after, list_item_t value)
{
    if (list == NULL) return NULL;

    node_t* node = malloc(sizeof(node_t));
    if (node == NULL) return NULL;
    node->value = value;

    if (insert_after == NULL)
    {
        // push front
        node->next = list->head;
        list->head = node;
    }
    else
    {
        insert_after->next = node;
    }

    if (insert_after == list->tail)
    {
        // push back
        node->next = NULL;
        list->tail = node;
    }
    else if (insert_after != NULL)
    {
        assert(insert_after->next != NULL);
        insert_after->next->prev = node;
    }

    node->prev = insert_after;

    ++list->count;
    return node;
}

node_t* list_remove(list_t* list, node_t* node)
{
    if (list == NULL || node == NULL) return NULL;

    node_t* result = node->next;
    if (node == list->head)
    {
        list->head = node->next;
    }
    else if (node == list->tail)
    {
        list->tail = node->prev;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    free(node);

    return result;
}

node_t* list_push_back(list_t* list, list_item_t value)
{
    if (list == NULL) return NULL;
    return list_insert(list, list->tail, value);
}

