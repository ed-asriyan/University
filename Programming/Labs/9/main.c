#include <stdlib.h>

#include "graph.h"

Graph* build_graph(FILE* f) {
	int vertex_count = 0;

	fscanf(f, "%d", &vertex_count);

	Graph* G = create_graph(vertex_count);

	while (!feof(f)) {
		int vertex_index = 0;
		int vertex = 0;

		fscanf(f, "%d %d", &vertex_index, &vertex);
		add_edge(G, vertex_index, vertex);
	}

	return G;
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		fprintf(stderr, "Invalid arguments.\n");
		return -1;
	}

	FILE* a = fopen(argv[1], "r");
	if (a != NULL) {
		Graph* a_graph = build_graph(a);

		fprintf(stdout, "TS  A: ");
		top_sort(a_graph);
		fprintf(stdout, "\n\n");

		clear_graph(a_graph);
		fclose(a);
	} else {
		fprintf(stderr, "Can not open file %s\n", argv[1]);
	}

	FILE* b = fopen(argv[2], "r");
	if (b != NULL) {
		Graph* b_graph = build_graph(b);

		fprintf(stdout, "BFS B: ");
		bfs(b_graph, 0);
		fprintf(stdout, "\n");
		fprintf(stdout, "DFS B: ");
		dfs(b_graph, 0);
		fprintf(stdout, "\n\n");

		clear_graph(b_graph);
		fclose(b);
	} else {
		fprintf(stderr, "Can not open file %s\n", argv[2]);
	}

	FILE* c = fopen(argv[3], "r");
	if (c != NULL) {
		Graph* c_graph = build_graph(c);

		fprintf(stdout, "BFS C: ");
		bfs(c_graph, 0);
		fprintf(stdout, "\n");
		fprintf(stdout, "DFS C: ");
		dfs(c_graph, 0);
		fprintf(stdout, "\n\n");

		clear_graph(c_graph);
		fclose(c);
	} else {
		fprintf(stderr, "Can not open file %s\n", argv[3]);
	}

	FILE* d = fopen(argv[4], "r");
	if (d != NULL) {
		Graph* build_graph1 = build_graph(d);

		fprintf(stdout, "BFS D: ");
		bfs(build_graph1, 0);
		fprintf(stdout, "\n");
		fprintf(stdout, "DFS D: ");
		dfs(build_graph1, 0);
		fprintf(stdout, "\n\n");

		clear_graph(build_graph1);
		fclose(d);
	} else {
		fprintf(stderr, "Can not open file %s\n", argv[4]);
	}

	return 0;
}