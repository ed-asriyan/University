//
// Created by lieroz on 02.12.16.
//

#include "heap.h"

MinHeapNode* NewMinHeapNode(int v, int dist) {
	MinHeapNode* min_heap_node = (MinHeapNode*) malloc(sizeof(MinHeapNode));

	min_heap_node->v = v;
	min_heap_node->dist = dist;

	return min_heap_node;
}

MinHeap* CreateMinHeap(int capacity) {
	MinHeap* min_heap = (MinHeap*) malloc(sizeof(MinHeap));

	min_heap->pos = (int*) malloc(capacity * sizeof(int));
	min_heap->size = 0;
	min_heap->capacity = capacity;
	min_heap->array = (MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));

	return min_heap;
}

void DestroyMinHeap(MinHeap* min_heap) {
	for (size_t i = 0; i < min_heap->size; ++i) {
		free(min_heap->array[i]);
	}

	free(min_heap->array);
	free(min_heap->pos);
	free(min_heap);
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void SwapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
	MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void MinHeapify(MinHeap* min_heap, int idx) {
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < min_heap->size &&
		min_heap->array[left]->dist < min_heap->array[smallest]->dist) {
		smallest = left;
	}

	if (right < min_heap->size &&
		min_heap->array[right]->dist < min_heap->array[smallest]->dist) {
		smallest = right;
	}

	if (smallest != idx) {
		// The nodes to be swapped in min heap
		MinHeapNode* smallestNode = min_heap->array[smallest];
		MinHeapNode* idx_node = min_heap->array[idx];

		// Swap positions
		min_heap->pos[smallestNode->v] = idx;
		min_heap->pos[idx_node->v] = smallest;

		// Swap nodes
		SwapMinHeapNode(&min_heap->array[smallest], &min_heap->array[idx]);

		MinHeapify(min_heap, smallest);
	}
}

int IsEmpty(MinHeap* min_heap) {
	return min_heap->size == 0;
}

MinHeapNode* ExtractMin(MinHeap* min_heap) {
	if (IsEmpty(min_heap)) {
		return NULL;
	}

	// Store the root node
	MinHeapNode* root = min_heap->array[0];

	// Replace root node with last node
	MinHeapNode* last_node = min_heap->array[min_heap->size - 1];
	min_heap->array[0] = last_node;

	// Update position of last node
	min_heap->pos[root->v] = min_heap->size - 1;
	min_heap->pos[last_node->v] = 0;

	// Reduce heap size and heapify root
	--min_heap->size;
	MinHeapify(min_heap, 0);

	return root;
}

void DecreaseKey(MinHeap* min_heap, int v, int dist) {
	// Get the index of v in  heap array
	int i = min_heap->pos[v];

	// Get the node and update its dist value
	min_heap->array[i]->dist = dist;

	// Travel up while the complete tree is not hepified.
	// This is a O(Logn) loop
	while (i && min_heap->array[i]->dist < min_heap->array[(i - 1) / 2]->dist) {
		// Swap this node with its parent
		min_heap->pos[min_heap->array[i]->v] = (i - 1) / 2;
		min_heap->pos[min_heap->array[(i - 1) / 2]->v] = i;
		SwapMinHeapNode(&min_heap->array[i], &min_heap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

bool IsInMinHeap(MinHeap* min_heap, int v) {
	if (min_heap->pos[v] < min_heap->size) {
		return true;
	}

	return false;
}
