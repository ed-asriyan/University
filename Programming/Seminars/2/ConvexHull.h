#ifndef __CONVEX_HULL_H__
#define __CONVEX_HULL_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
	double x;
	double y;
} Point;

// graham scan algorithm
int graham_scan(Point* source, int count, Point* result);


// prints point into the stream
int print_point(FILE* stream, Point* p);

// scans point from the stream
int scan_point(FILE* stream, Point* p);

#endif // __CONVEX_HULL__
