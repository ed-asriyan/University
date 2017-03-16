//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_MODEL_H
#define INC_3DVIEW_MODEL_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "math.h"
#include "errors.h"
#include "canvas.h"

typedef struct {
	int a, b;
} edge_t;

typedef struct {
	bool is_loaded;
	int vertex_count;
	int edge_count;
	vector_t* vertices;
	edge_t* edges;
} model_t;

void model_initialize(model_t* model);
error_t model_load(model_t* model, const char* file_path);
bool model_is_loaded(const model_t* model);
error_t model_render(const model_t* model, const matrix_t* object_to_canvas, const canvas_t* canvas);
void model_deinitialize(model_t* model);

error_t model_read(model_t* model, FILE* file);

#endif //INC_3DVIEW_MODEL_H
