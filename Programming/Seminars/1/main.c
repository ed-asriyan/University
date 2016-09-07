#include <stdio.h>

#include "PolygoneArea.h"

int main(void)
{
    double result;
    calc_area(stdin, &result);

    printf("%lf\n", result);
	return 0;
}
