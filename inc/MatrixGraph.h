#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Matrix.h"
#include "HeapQueue.h"

class MatrixGraph : public Graph
{
	Matrix<ulint> * adjacency_matrix_;

public:
	MatrixGraph();
	~MatrixGraph();

	void read_file(const std::string & name);
	Vector<ulint> & operator[] (ulint index);
	void generate_random(ulint size, double density);
	void solve_dijkstra();
	void solve_bellman_ford();
};

std::ostream & operator << (std::ostream & out, MatrixGraph & graph);
#endif
