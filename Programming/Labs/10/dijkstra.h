//
// Created by lieroz on 02.12.16.
//

#ifndef LAB_10_DIJKSTRA_H
#define LAB_10_DIJKSTRA_H

#include <limits.h>

#include "graph.h"

// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void DijkstraShortestDistance(Graph*, int);

#endif //LAB_10_DIJKSTRA_H
