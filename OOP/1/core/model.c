//
// Created by ed on 07.03.17.
//

#include "model.h"

void model_initialize(model_t* model) {
	model->is_loaded = false;
}

error_t model_load(model_t* model, const char* file_path) {
	FILE* file = fopen(file_path, "r");
	if (!file) {
		return UNABLE_TO_OPEN_FILE;
	}
	model_t new_model;
	model_initialize(&new_model);
	error_t error = model_read(&new_model, file);
	if (error == NONE) {
		model_deinitialize(model);
		*model = new_model;
	}
	fclose(file);
	return error;
}

bool model_is_loaded(const model_t* model) {
	return model->is_loaded;
}

error_t model_render(const model_t* model, const matrix_t* object_to_canvas) {
	if (!model->is_loaded) {
		return MODEL_NOT_LOADED;
	}
	for (int i = 0; i < model->edge_count; ++i) {
		edge_t edge = model->edges[i];
		const vector_t vector = model->vertices[edge.a];
		vector_t edge_vertex_a = vector_transform(&vector, object_to_canvas);
		const vector_t vector1 = model->vertices[edge.b];
		vector_t edge_vertex_b = vector_transform(&vector1, object_to_canvas);
		draw_line(&edge_vertex_a, &edge_vertex_b);
	}
	return NONE;
}

void model_deinitialize(model_t* model) {
	if (!model->is_loaded) {
		return;
	}
	free(model->vertices);
	free(model->edges);
}

static bool read_int(int* value, FILE* file) {
	return fscanf(file, "%d", value) == 1;
}

static bool read_double(double* value, FILE* file) {
	return fscanf(file, "%lf", value) == 1;
}

static bool read_header(model_t* model, FILE* file) {
	return read_int(&model->vertex_count, file) && read_int(&model->edge_count, file);
}

static bool read_vertex(vector_t* vertex, FILE* file) {
	return read_double(&vertex->x, file) && read_double(&vertex->y, file) && read_double(&vertex->z, file);
}

static bool read_vertices(vector_t* vertices, int vertex_count, FILE* file) {
	bool ok = true;
	for (int i = 0; i < vertex_count && (ok = read_vertex(&vertices[i], file)); ++i);
	return ok;
}

static bool read_edge(edge_t* edge, FILE* file) {
	return read_int(&edge->a, file) && read_int(&edge->b, file);
}

static bool read_edges(edge_t* edges, int edge_count, FILE* file) {
	bool ok = true;
	for (int i = 0; i < edge_count && (ok = read_edge(&edges[i], file)); ++i);
	return ok;
}

static bool read_body(model_t* model, FILE* file) {
	return read_vertices(model->vertices, model->vertex_count, file)
		&& read_edges(model->edges, model->edge_count, file);
}

static bool allocate_body(model_t* model) {
	bool ok = false;
	if ((model->vertices = (vector_t*) malloc(model->vertex_count * sizeof(vector_t)))) {
		if ((model->edges = (edge_t*) malloc(model->edge_count * sizeof(edge_t)))) {
			ok = true;
		} else {
			free(model->vertices);
		}
	}
	return ok;
}

error_t model_read(model_t* model, FILE* file) {
	error_t error = NONE;
	if (read_header(model, file)) {
		if (!allocate_body(model)) {
			error = OUT_OF_MEMORY;
		} else if (!read_body(model, file)) {
			free(model->vertices);
			free(model->edges);
			error = INVALID_FILE;
		} else {
			model->is_loaded = true;
		}
	} else {
		error = INVALID_FILE;
	}
	return error;
}