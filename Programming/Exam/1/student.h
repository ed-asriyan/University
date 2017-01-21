#ifndef __STUDENT__H__
#define __STUDENT__H__

#include <stdlib.h>
#include <stdio.h>

struct Student
{
    char name[16];
    int mark[3];
};

typedef struct Student student_t;

int scan_student(FILE* file, student_t* student);

int print_student(student_t* student);

double average_mark_student(student_t* student);

#endif