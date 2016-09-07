#ifndef __POLYGONE_AREA_H__
#define __POLYGONE_AREA_H__

#include <stdio.h>

#define ERROR_NULL_REFERENCE -1
#define ERROR_STREAM -2
#define ERROR_VALUES -3

typedef struct 
{
    double x;
    double y;
} Point;

int read_point(FILE* input, Point* result);
int calc_area(FILE* input, double* result);



#endif // __POLYGONE_AREA_H__
