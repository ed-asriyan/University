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

int main() {
	FILE* a = fopen("Examples/a.txt", "r");
	Graph* A = BuildGraph(a);

	fprintf(stdout, "\033[0;32m"); // changes the color of output text
	fprintf(stdout, "ShortestDistance A:\n");
	DijkstraShortestDistance(A, 0);
	fprintf(stdout, "\n\n");

	DestroyGraph(A);
	fclose(a);

	FILE* b = fopen("Examples/b.txt", "r");
	Graph* B = BuildGraph(b);

	fprintf(stdout, "ShortestDistance B:\n");
	DijkstraShortestDistance(B, 0);
	fprintf(stdout, "\n\n");

	DestroyGraph(B);
	fclose(b);

	FILE* c = fopen("Examples/c.txt", "r");
	Graph* C = BuildGraph(c);

	fprintf(stdout, "ShortestDistance C:\n");
	DijkstraShortestDistance(C, 0);
	fprintf(stdout, "\n\n");

	DestroyGraph(C);
	fclose(c);

	FILE* d = fopen("Examples/d.txt", "r");
	Graph* D = BuildGraph(d);

	fprintf(stdout, "ShortestDistance D:\n");
	DijkstraShortestDistance(D, 0);

	DestroyGraph(D);
	fclose(d);

	return 0;
}