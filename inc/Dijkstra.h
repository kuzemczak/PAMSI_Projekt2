#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <climits>
#include <fstream>

#include "utils.h"
#include "Graph.h"
#include "ListGraph.h"
#include "HeapQueue.h"
#include "MatrixGraph.h"

void Dijkstra(Graph & graph);
void innerLoop(ListGraph & graph, 
	HeapQueue<int> & nonVisited, 
	ulint * indices, 
	ulint * predecessors, 
	ulint & currentNumber,
	ulint & currentCost);
void innerLoop(MatrixGraph & graph,
	HeapQueue<int> & nonVisited,
	ulint * indices,
	ulint * predecessors,
	ulint & currentNumber,
	ulint & currentCost);
void toFile(Graph & graph, ulint * predecessors, ulint * visited);
#endif
