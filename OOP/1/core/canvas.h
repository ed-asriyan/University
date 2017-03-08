//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_CANVAS_H
#define INC_3DVIEW_CANVAS_H

#include <GL/glut.h>

#include "math.h"

unsigned get_width();
unsigned get_height();
void draw_line(const vector_t* point_a, const vector_t* point_b);

#endif //INC_3DVIEW_CANVAS_H
