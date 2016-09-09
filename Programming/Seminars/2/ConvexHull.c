#include "ConvexHull.h"

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