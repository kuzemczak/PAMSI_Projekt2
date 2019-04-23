#include "Dijkstra.h"

typedef Neighbour Node;


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
		nonVisited.push(i, INF);
		visited[i] = INF;
		predecessors[i] = INF;
	}


	// obtaining indices from heap
	getIndices(nonVisited, indices);

	// setting starting node's path cost as 0
	// the heap automatically recovers
	nonVisited.set_item_key(indices[graph.starting_node()], 0);

	while (nonVisited.size() > 0)
	{
		ulint currentCost = nonVisited.get_key(0);
		ulint currentNumber = nonVisited.pop_front();
		getIndices(nonVisited, indices);
		
		if (typeid(graph) == typeid(ListGraph))
		{
			innerLoop(dynamic_cast<ListGraph&>(graph), 
				nonVisited, 
				indices, 
				predecessors, 
				currentNumber, 
				currentCost);
		}
		else if (typeid(graph) == typeid(MatrixGraph))
		{
			innerLoop(dynamic_cast<MatrixGraph&>(graph),
				nonVisited,
				indices,
				predecessors,
				currentNumber,
				currentCost);
		}
		visited[currentNumber] = currentCost;
	}

	toFile(graph, predecessors, visited);
}

void innerLoop(ListGraph & graph, HeapQueue<int> & nonVisited,
	ulint * indices, 
	ulint * predecessors, 
	ulint & currentNumber,
	ulint & currentCost)
{
	for (Neighbour neigh : graph[currentNumber])
	{
		if (nonVisited.contains(neigh.number) &&
			nonVisited.get_key(indices[neigh.number]) > currentCost + neigh.path_cost)
		{
			nonVisited.set_item_key(indices[neigh.number], currentCost + neigh.path_cost);
			predecessors[neigh.number] = currentNumber;
			getIndices(nonVisited, indices);
		}
	}
}

void innerLoop(MatrixGraph & graph, HeapQueue<int> & nonVisited,
	ulint * indices,
	ulint * predecessors,
	ulint & currentNumber,
	ulint & currentCost)
{
	for (ulint i = 0; i < graph.size(); i++)
	{
		if (graph[currentNumber][i] != 0 && nonVisited.contains(i) &&
			nonVisited.get_key(indices[i]) > currentCost + graph[currentNumber][i])
		{
			nonVisited.set_item_key(indices[i], currentCost + graph[currentNumber][i]);
			predecessors[i] = currentNumber;
			getIndices(nonVisited, indices);
		}
	}
}

void toFile(Graph & graph, ulint * predecessors, ulint * visited)
{
	std::ofstream file;
	file.open("data/Dijkstra_result.txt", std::ios::out);
	if (!file.is_open())
		throw 3;

	for (ulint i = 0; i < graph.size(); i++)
	{
		file << i << ": ";
		Vector<ulint> path;
		path.push_back(i);
		while (path[path.size() - 1] != graph.starting_node() &&
			predecessors[path[path.size() - 1]] < graph.size())
		{
			path.push_back(predecessors[path[path.size() - 1]]);
		}
		file << path.pop_back();
		while (path.size() > 0)
		{
			file << "->" << path.pop_back();
		}
		file << "\t[" << visited[i] << "]" << std::endl;
	}
	file.close();
}