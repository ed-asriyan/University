#include <stdlib.h>
#include <stdio.h>

#include "list.h"

list_t* scan_list(FILE* in)
{
    if (in == NULL) return NULL;

    list_t* result = list_create();
    if (result == NULL) return NULL;
    while (!feof(in))
    {
        student_t student;
        if (scan_student(in, &student) != 1 || list_push_back(result, student) == NULL)
        {
            list_free(result);
            return NULL;
        }
    }
    return result;
}

int print_list(FILE* out, list_t* list)
{
    if (out == NULL || list == NULL) return 0;

    node_t* node = list->head;
    while (node != NULL)
    {
        print_student(&node->value);
        node = node->next;
    }

    return 1;
}

double calc_average_mark(list_t* list)
{
    if (list == NULL) return 0;

    double result = 0;
    node_t* node = list->head;
    while (node != NULL)
    {
        result += average_mark_student(&node->value);
        node = node->next;
    }

    return result / list->count;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: Wrong argument number\n");
        return -1;
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error: Can not open the file.\n");
        return -2;
    }

    list_t* list = scan_list(f);
    if (list == NULL)
    {
        fprintf(stderr, "Error: malloc error\n");
        fclose(f);
        return -3;
    }
    printf("Source list:\n");
    print_list(stdout, list);
    printf("\n");

    double average = calc_average_mark(list);
    printf("Average mark: %lf\n\n", average);

    unsigned int count = list->count;
    node_t* node = list->head;
    for (int i = 0; i < count; ++i)
    {
        if (average_mark_student(&node->value) < average)
        {
            student_t student = node->value;
            node = list_remove(list, node);
            list_push_back(list, student);
        }
        else
        {
            node = node->next;
        }
    }

    printf("Result list:\n");
    print_list(stdout, list);
    printf("\n");

    list_free(list);

    fclose(f);

    return 0;
}

