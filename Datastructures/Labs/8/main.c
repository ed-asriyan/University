#include <stdlib.h>

#include "graph.h"
#include "dijkstra.h"

Graph* BuildGraph(FILE* f) {
	int vertex_count = 0;

	fscanf(f, "%d", &vertex_count);
	Graph* G = CreateGraph(vertex_count);

	while (!feof(f)) {
		int vertex_index = 0;
		int vertex = 0;
		int weight = 0;

		fscanf(f, "%d %d %d", &vertex_index, &vertex, &weight);
		AddEdge(G, vertex_index, vertex, weight);
	}

	return G;
}

int main(const int argc, const char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "ERROR: INVALID ARGUMENTS!");
		return -1;
	}

	int longest_path = atoi(argv[2]);
	FILE* a = fopen(argv[1], "r");
	Graph* A = BuildGraph(a);

	DijkstraShortestDistance(A, 0, longest_path);
	fprintf(stdout, "\n\n");

	DestroyGraph(A);
	fclose(a);

	return 0;
}