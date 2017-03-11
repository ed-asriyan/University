//
// Created by lieroz on 02.12.16.
//

#include "graph.h"

// A utility function to create a new adjacency list node
AdjListNode* NewAdjListNode(int dest, int weight) {
	AdjListNode* new_node = (AdjListNode*) malloc(sizeof(struct AdjListNode));

	new_node->dest = dest;
	new_node->weight = weight;
	new_node->next = NULL;

	return new_node;
}

Graph* CreateGraph(int V) {
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->V = V;

	// Create an array of adjacency lists.  Size of array will be V
	graph->array = (AdjList*) malloc(V * sizeof(AdjList));

	// Initialize each adjacency list as empty by making head as NULL
	for (int i = 0; i < V; ++i) {
		graph->array[i].head = NULL;
	}

	return graph;
}

void DestroyGraph(Graph* graph) {
	for (size_t i = 0; i < graph->V; ++i) {
		AdjListNode* p_crawler = graph->array[i].head;

		while (p_crawler != NULL) {
			AdjListNode* temp = p_crawler;
			p_crawler = p_crawler->next;
			free(temp);
		}

		graph->array[i].head = NULL;
	}

	free(graph->array);
	free(graph);
}


void AddEdge(Graph* graph, int src, int dest, int weight) {
	// Add an edge from src to dest.  A new node is added to the adjacency
	// list of src.  The node is added at the begining
	AdjListNode* new_node = NewAdjListNode(dest, weight);
	new_node->next = graph->array[src].head;
	graph->array[src].head = new_node;

	// Since graph is undirected, add an edge from dest to src also
	new_node = NewAdjListNode(src, weight);
	new_node->next = graph->array[dest].head;
	graph->array[dest].head = new_node;
}