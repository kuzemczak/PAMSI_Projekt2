#ifndef TESTS_H
#define TESTS_H

#include <chrono>
#include <fstream>

#include "MatrixGraph.h"
#include "ListGraph.h"

typedef std::chrono::high_resolution_clock Clock;

enum TestedAlgorithm {DIJKSTRA, BELLMAN_FORD};

struct namedGraph
{
	Graph *graph;
	std::string name;
	namedGraph() : graph(NULL), name("") {}
	namedGraph(Graph* g, const std::string& nam)
	{
		graph = g;
		name = nam;
	}
	Graph *operator->() const
	{
		return graph;
	}
};

void testGraphAlgorithm(TestedAlgorithm algorithm, const Vector<ulint> & sizes, const Vector<double> & densities, ulint iterations);

#endif
