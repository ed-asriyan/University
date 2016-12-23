//
// Created by lieroz on 29.11.16.
// Modified by ed 07.12.16.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dequeue.h"

#ifndef LAB_09_MATRIX_H
#define LAB_09_MATRIX_H

typedef struct {
	int vertex_count;
	Dequeue** adjacency_lists;
} Graph;

Graph* create_graph(int);
void clear_graph(Graph*);

void add_edge(Graph*, int, int);

void bfs(Graph*, int);
void dfs(Graph*, int);

void top_sort(Graph*);

#endif //LAB_09_MATRIX_H
