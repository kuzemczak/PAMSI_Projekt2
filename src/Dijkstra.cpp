#include "Dijkstra.h"

typedef Neighbour Node;

template<typename T>
void getIndices(HeapQueue<T> & heap, ulint * indices);

void Dijkstra(Graph & graph)
{
	// element's data is node's number,
	// element's key is node's path cost from starting node
	HeapQueue<int> nonVisited;

	// element's index is node's number,
	// element's value is node's index on heap
	ulint * indices = new ulint[graph.size()];

	// element's index is node's number,
	// element's value is node's path cost from starting node
	ulint * visited = new ulint[graph.size()];

	// index is node's number,
	// value is node's predecessor in shortest path
	ulint * predecessors = new ulint[graph.size()];

	// filling the heap
	for (ulint i = 0; i < graph.size(); i++)
	{
		nonVisited.push(i, UINT_MAX);
		visited[i] = UINT_MAX;
		predecessors[i] = UINT_MAX;
	}


	// obtaining indices from heap
	getIndices(nonVisited, indices);

	// setting path cost to starting node as 0
	// the heap automatically recovers
	nonVisited.set_item_key(indices[graph.starting_node()], 0);

	while (nonVisited.size() > 0)
	{
		ulint currentCost = nonVisited.get_key(0);
		ulint currentNumber = nonVisited.pop_front();
		getIndices(nonVisited, indices);

		for (list_iterator<Neighbour> it = graph[currentNumber].begin();
			it != graph[currentNumber].end(); it++)
		{
			if (nonVisited.contains((*it).number) &&
				nonVisited.get_key(indices[(*it).number]) > currentCost + (*it).path_cost)
			{
				nonVisited.set_item_key(indices[(*it).number], currentCost + (*it).path_cost);
				predecessors[(*it).number] = currentNumber;
				getIndices(nonVisited, indices);
			}
		}

		visited[currentNumber] = currentCost;
	}

	std::ofstream file;
	file.open("data/Dijkstra_result.txt", std::ios::out);
	if (!file.is_open())
		throw 3;

	for (ulint i = 0; i < graph.size(); i++)
	{
		file << i << ": ";
		Vector<ulint> path;
		path.push_back(i);
		while (path[path.size() - 1] != graph.starting_node())
		{
			path.push_back(predecessors[path[path.size() - 1]]);
		}
		file << path.pop_back();
		while (path.size() > 0)
		{
			file << "->" << path.pop_back();
		}
		file << std::endl;
	}
	file.close();
}

template<typename T>
void getIndices(HeapQueue<T> & heap, ulint * indices)
{
	for (ulint i = 0; i < heap.size(); i++)
	{
		indices[heap[i]] = i;
	}
}