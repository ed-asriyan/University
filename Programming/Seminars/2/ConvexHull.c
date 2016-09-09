#include "ConvexHull.h"

// prints point into the stream
int print_point(FILE* stream, Point* p)
{
    return fprintf(stream, "%3.0lf %3.0lf", p->x, p->y);
}

// scans point from the stream
int scan_point(FILE* stream, Point* p)
{
    return fscanf(stream, "%lf %lf", &(p->x), &(p->y));
}

// swap two points
void swap(Point* a, Point* b)
{
    Point tmp = *a;
    *a = *b;
    *b = tmp;
}

// comparing two points
int point_cmp(Point* p1, Point* p2)
{
    if (p1->y < p2->y) {
        return -1;
    } else if (p1->y == p2->y) {
        if (p1->x < p2->x) {
            return -1;
        } else if (p1->x == p2->x) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}

// returns square of distance between two points
double sqr_dist(Point* a, Point* b)
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;

    return dx * dx + dy * dy;
}

//  1 - if ABC forms clockwise turn;
//  0 - if ABC are collinear;
// -1 - if ABC forms couner-clockwise turn
int ccw(Point* a, Point* b, Point* c)
{
    int area = (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);

    if (area > 0) {
        return -1;
    } else if (area < 0) {
        return 1;
    } else {
        return 0;
    }
}

// compares two points (a and b) in sort algorithm
int sort_cmp(Point* pivot, Point* a, Point* b)
{
    int turn = ccw(pivot, a, b);
    if (turn == 0) {
        return sqr_dist(pivot, a) < sqr_dist(pivot, b);
    } else {
        return turn == -1;
    }
}

// sorts the point array a by polar angle relative to the point pivot
void quick_sort_points(Point* pivot, Point* a, int count)
{
    if (count < 2) {
        return;
    }

    int i, j;
    Point* p = a + (count / 2);
    Point tmp;

    for (i = 0, j = count - 1; ; ++i, --j) {
        while (sort_cmp(pivot, a + i, p) > 0) {
            ++i;
        }
        while (sort_cmp(pivot, p, a + j) > 0) {
            --j;
        }
        if (i >= j) {
            break;
        }

        swap(a + i, a + j);
    }

    quick_sort_points(pivot, a, i);
    quick_sort_points(pivot, a + i, count - i);
}

// graham scan algorithm
int graham_scan(Point* source, int count, Point* result)
{
    if (count < 2) {
        return -1;
    }
    if (count < 3) {
        memcpy(result, source, sizeof(Point) * count);
        return count;
    }

    // find the point having the least y coordinate (pivot),
    // ties are broken in favor of lower x coordinate
    int least_y = 0;
    for (int i = 1; i < count; ++i) {
        if (point_cmp(source + i, source + least_y) < 0) {
            least_y = i;
        }
    }

    // swapping the pivot with the 1st point
    swap(source, source + least_y);

    // sorting remaining roints by polar angle
    quick_sort_points(source, source + 1, count - 1);

    // the last algorithm part
    memcpy(result, source, sizeof(Point) * 3); // the first three points 
                                               // are identical with source
    int result_size = 3;
    for (int i = 3; i < count; ++i) {
        Point top = result[result_size - 1];
        --result_size;

        // wikipedia tells that the following while condition must be such as
        //  ccw(result + (result_size - 1), &top, source + i) <= 0
        // but it doesn't works in this code. i tried "play with code" and
        // i think i found a solution
        while (ccw(result + (result_size - 1), &top, source + i) >= 0) {
            top = result[result_size - 1];
            --result_size;
        }

        result[result_size++] = top;
        result[result_size++] = source[i];
    }

    return result_size;
}