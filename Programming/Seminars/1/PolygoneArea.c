#include "PolygoneArea.h" 

int read_point(FILE* input, Point* result)
{
    if (input == NULL ||
        result == NULL){
        return ERROR_NULL_REFERENCE; 
    }
    
    int scan_result = fscanf(input, "%lf %lf", &(result->x), &(result->y));
    
    return scan_result == 2 ? 0 : ERROR_STREAM;
}

double double_area(const Point* p1, const Point* p2)
{
    return (p1->y + p2->y) * (p1->x - p2->x);
}

int calc_area(FILE* input, double* result)
{
    if (input == NULL ||
        result == NULL){
        return ERROR_NULL_REFERENCE;
    }
 
    int count = 1;   
    double _result = 0;

    Point first_point;
    read_point(input, &first_point);

    Point point0 = first_point;
    Point point1;
    while (!read_point(input, &point1))
    {
        _result += double_area(&point0, &point1);
        point0 = point1;

        count++;
    }
    _result += double_area(&point1, &first_point);

    *result = _result / 2;
    return count > 2 && _result > 0 ? 0 : ERROR_VALUES;
}
