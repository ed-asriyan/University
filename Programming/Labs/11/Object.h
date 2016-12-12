#ifndef __OBJECT_H_DEF__
#define __OBJECT_H_DEF__

#include <stdio.h>

#define OBJECT_FEATURE_COUNT 7

#define OBJECT_FEATURE_1      order_ID
#define OBJECT_FEATURE_2   customer_ID
#define OBJECT_FEATURE_3   employee_ID
#define OBJECT_FEATURE_4    order_date
#define OBJECT_FEATURE_5 required_date
#define OBJECT_FEATURE_6  shipped_date
#define OBJECT_FEATURE_7       freight

typedef struct {
    int    OBJECT_FEATURE_1;
    char*  OBJECT_FEATURE_2;
    int    OBJECT_FEATURE_3;
    char*  OBJECT_FEATURE_4;
    char*  OBJECT_FEATURE_5;
    char*  OBJECT_FEATURE_6;
    double OBJECT_FEATURE_7;
} Object;

#endif // __OBJECT_H_DEF__