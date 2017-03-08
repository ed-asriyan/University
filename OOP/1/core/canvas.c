//
// Created by ed on 07.03.17.
//

#include "canvas.h"

unsigned get_width(const canvas_t* canvas) {
	return (unsigned) glutGet(GLUT_WINDOW_WIDTH);
}

unsigned get_height(const canvas_t* canvas) {
	return (unsigned) glutGet(GLUT_WINDOW_HEIGHT);
}

void draw_line(canvas_t* canvas, const vector_t* point_a, const vector_t* point_b) {
	glVertex2d(point_a->x, point_a->y);
	glVertex2d(point_b->x, point_b->y);
}
