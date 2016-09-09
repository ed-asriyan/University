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