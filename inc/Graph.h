#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>

#include "Vector.h"
#include "List.h"

class Neighbour
{
public:
	ulint number;
	unsigned int path_cost;

	Neighbour(ulint num, ulint cost) : number(num), path_cost(cost) {}
};

class Graph
{
	List<Neighbour> * adjacency_list_;
	ulint starting_node_;
	ulint size_;
public:
	Graph();
	~Graph();

	void add_neighbour(ulint nodeNum, ulint neighbourNum, ulint pathCost);
	
	void read_file(const std::string & name);

	ulint size();
	ulint starting_node();
	List<Neighbour> & operator [] (ulint index);
};

std::ostream & operator << (std::ostream & out, Graph & graph);

#endif