#include <stdio.h>

#include "ConvexHull.h"

int main(void)
{
	// source points count
	int count;
	scanf("%d", &count);

	// reading source points
	Point* source = (Point*)malloc(sizeof(Point) * count);
	for (int i = 0; i < count; ++i) {
		scan_point(stdin, source + i);
	}

	// graham scan algorithm result
	Point* hull = (Point*)malloc(sizeof(Point) * count);

	// running graham scan algorithm
	int hull_size = graham_scan(source, count, hull);
	if (hull_size <= 0) {
		printf("Error occured (code %d)\n", hull_size);
	} else {
		for (int i = 0; i < hull_size; ++i) {
			print_point(stdout, hull + i);
			printf("\n");
		}
	}

	free(hull);
	free(source);

    return 0;
}
