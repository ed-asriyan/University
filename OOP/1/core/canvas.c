//
// Created by ed on 07.03.17.
//

#include "canvas.h"

unsigned get_width() {
	return 500;
}

unsigned get_height() {
	return 500;
}

void draw_line(const vector_t* point_a, const vector_t* point_b) {
	glVertex2d(point_a->x, point_a->y);
	glVertex2d(point_b->x, point_b->y);
}
