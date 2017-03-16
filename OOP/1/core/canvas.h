//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_CANVAS_H
#define INC_3DVIEW_CANVAS_H

#include "math.h"

typedef struct {
	unsigned int width;
	unsigned int height;
	void (* draw_line)(const vector_t*, const vector_t*);
} canvas_t;

#endif //INC_3DVIEW_CANVAS_H
