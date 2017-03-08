//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_CANVAS_H
#define INC_3DVIEW_CANVAS_H

#include <GL/glut.h>

#include "math.h"

typedef struct canvas canvas_t;

unsigned get_width(const canvas_t* canvas);
unsigned get_height(const canvas_t* canvas);
void draw_line(canvas_t* canvas, const vector_t* point_a, const vector_t* point_b);

#endif //INC_3DVIEW_CANVAS_H
