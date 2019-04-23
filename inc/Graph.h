#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"
#include "HeapQueue.h"

#define TO_FILE_AND_COUT

class Graph
{
protected:
	ulint starting_node_;
	ulint size_;
	ulint * predecessors;
	ulint * shortest_paths;
public:
	Graph();
	~Graph();

	virtual void read_file(const std::string & name) = 0;
	virtual void generate_random(ulint size, double density) = 0;
	virtual void solve_dijkstra() = 0;
	virtual void solve_bellman_ford() = 0;
	ulint size();
	ulint starting_node();
	void toFile(const std::string & s);
};

template<typename T>
void getIndices(HeapQueue<T> & heap, ulint * indices)
{
	for (ulint i = 0; i < heap.size(); i++)
	{
		indices[heap[i]] = i;
	}
}

#endif