#include <stdio.h>

#include "PolygoneArea.h"

int main(void)
{
    double result;
    int result_code = calc_area(stdin, &result);

    if (result_code){
        printf("Error occured (code %d)", result_code);
    } else {
        printf("%lf", result);
    }

    printf("\n");
	return 0;
}
