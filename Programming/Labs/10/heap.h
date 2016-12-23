//
// Created by lieroz on 02.12.16.
//

#ifndef LAB_10_HEAP_H
#define LAB_10_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a min heap node
typedef struct {
	int v;
	int dist;
} MinHeapNode;

// Structure to represent a min heap
typedef struct {
	int size;      // Number of heap nodes present currently
	int capacity;  // Capacity of min heap
	int* pos;     // This is needed for DecreaseKey()
	MinHeapNode** array;
} MinHeap;

// An utility function to create a new Min Heap Node
MinHeapNode* NewMinHeapNode(int, int);

// A utility function to create a Min Heap
MinHeap* CreateMinHeap(int);

// An utility function to destroy Min Heap
void DestroyMinHeap(MinHeap*);

// A utility function to check if the given minHeap is ampty or not
int IsEmpty(MinHeap*);

// Standard function to extract minimum node from heap
MinHeapNode* ExtractMin(MinHeap*);

// Function to decrease dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void DecreaseKey(MinHeap*, int, int);

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool IsInMinHeap(MinHeap*, int);

#endif //LAB_10_HEAP_H
