#include "student.h"

int scan_student(FILE* file, student_t* student)
{
    if (file == NULL || student == NULL) return 0;
    int read_result = fscanf(file,
                             "%s %d %d %d",
                             student->name,
                             &student->mark[0],
                             &student->mark[1],
                             &student->mark[2]);
    switch (read_result)
    {
        case 4:
            return 1;
        case EOF:
            return EOF;
        default:
            return 0;
    }
}

int print_student(student_t* student)
{
    if (student == NULL) return 0;
    if (fprintf(stdout,
                "%15s %3d %3d %3d | %4lf\n",
                student->name,
                student->mark[0],
                student->mark[1],
                student->mark[2],
                average_mark_student(student)) == 4)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

double average_mark_student(student_t* student)
{
    if (student == NULL) return 0;
    return (double)(student->mark[0] + student->mark[1] + student->mark[2]) / 3;
}

