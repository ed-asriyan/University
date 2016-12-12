//
// Created by lieroz on 02.12.16.
//

#include "dijkstra.h"

// Function to print shortest path from source to j
// using parent array
void PrintPath(int parent[], int j) {
	// Base Case : If j is source
	if (parent[j] == -1) {
		return;
	}

	PrintPath(parent, parent[j]);

	fprintf(stdout, "%d ", j);
}

// A utility function used to print the solution
void PrintArr(int dist[], int n, int parent[]) {
	int src = 0;
	fprintf(stdout, "Vertex\t\tDistance\t\tPath");

	for (int i = 1; i < n; i++) {
		fprintf(stdout, "\n%d -> %d\t\t\t%d\t\t\t%d ", src, i, dist[i], src);
		PrintPath(parent, i);
	}
}

void DijkstraShortestDistance(Graph* graph, int src) {
	int V = graph->V;// Get the number of vertices in graph
	int dist[V];      // dist values used to pick minimum weight edge in cut
	int parent[V];

	// minHeap represents set E
	MinHeap* min_heap = CreateMinHeap(V);

	// Initialize min heap with all vertices. dist value of all vertices
	for (int v = 0; v < V; ++v) {
		parent[0] = -1;
		dist[v] = INT_MAX;
		min_heap->array[v] = NewMinHeapNode(v, dist[v]);
		min_heap->pos[v] = v;
	}

	// Make dist value of src vertex as 0 so that it is extracted first
	min_heap->array[src]->v = src;
	min_heap->array[src]->dist = dist[src];
	min_heap->pos[src] = src;
	dist[src] = 0;
	DecreaseKey(min_heap, src, dist[src]);

	// Initially size of min heap is equal to V
	min_heap->size = V;

	// In the following loop, min heap contains all nodes
	// whose shortest distance is not yet finalized.
	while (!IsEmpty(min_heap)) {
		// Extract the vertex with minimum distance value
		MinHeapNode* min_heap_node = ExtractMin(min_heap);
		int u = min_heap_node->v; // Store the extracted vertex number

		// Traverse through all adjacent vertices of u (the extracted
		// vertex) and update their distance values
		AdjListNode* p_crawl = graph->array[u].head;
		while (p_crawl != NULL) {
			int v = p_crawl->dest;

			// If shortest distance to v is not finalized yet, and distance to v
			// through u is less than its previously calculated distance
			if (IsInMinHeap(min_heap, v) && dist[u] != INT_MAX &&
				p_crawl->weight + dist[u] < dist[v]) {
				dist[v] = dist[u] + p_crawl->weight;
				parent[v] = u;
				// update distance value in min heap also
				DecreaseKey(min_heap, v, dist[v]);
			}
			p_crawl = p_crawl->next;
		}

		free(min_heap_node);
	}

	// print the calculated shortest distances
	PrintArr(dist, V, parent);
	DestroyMinHeap(min_heap);
}