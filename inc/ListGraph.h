#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <iostream>
#include <string>

#include "Vector.h"
#include "List.h"
#include "Graph.h"

class Neighbour
{
public:
	ulint number;
	unsigned int path_cost;

	Neighbour(ulint num, ulint cost) : number(num), path_cost(cost) {}
};

class ListGraph : public Graph
{
	List<Neighbour> * adjacency_list_;

	bool listContains(ulint node, ulint neighbourNumber);
public:
	ListGraph();
	~ListGraph();

	void add_neighbour(ulint nodeNum, ulint neighbourNum, ulint pathCost);
	
	void read_file(const std::string & name);
	List<Neighbour> & operator [] (ulint index);
	void generate_random(ulint size, double density);
	void solve_dijkstra();
	void solve_bellman_ford();
};

std::ostream & operator << (std::ostream & out, ListGraph & graph);


#endif