//
// Created by lieroz on 02.12.16.
//

#ifndef LAB_10_GRAPH_H
#define LAB_10_GRAPH_H

#include "heap.h"

// A structure to represent a node in adjacency list
typedef struct AdjListNode {
	int dest;
	int weight;
	struct AdjListNode* next;
} AdjListNode;

// A structure to represent an adjacency list
typedef struct {
	AdjListNode* head;  // pointer to head node of list
} AdjList;

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
typedef struct {
	int V;
	AdjList* array;
} Graph;

// A utility function that creates a graph of V vertices
Graph* CreateGraph(int);

// An utility function to destroy Graph
void DestroyGraph(Graph*);

// Adds an edge to an undirected graph
void AddEdge(Graph*, int, int, int);

#endif //LAB_10_GRAPH_H
