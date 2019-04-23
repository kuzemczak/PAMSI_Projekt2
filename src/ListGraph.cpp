#include <fstream>

#include "ListGraph.h"


ListGraph::ListGraph()
{
	adjacency_list_ = NULL;
}


ListGraph::~ListGraph()
{
}

void ListGraph::add_neighbour(ulint nodeNum, ulint neighbourNum, ulint pathCost)
{
	adjacency_list_[nodeNum].push(Neighbour(neighbourNum, pathCost));
}

void ListGraph::read_file(const std::string & name)
{
	std::ifstream file;
	file.open(name.c_str(), std::ios::in);

	if (!file.is_open())
		throw 3;

	ulint edges, node, neighbour, cost;

	if (!(file >> edges && file >> node && file >> cost))
	{
		file.close();
		throw 4;
	}

	starting_node_ = cost;
	size_ = node;
	if(adjacency_list_ != NULL)
		delete[] adjacency_list_;
	adjacency_list_ = new List<Neighbour>[node];

	for (int i = 0; i < edges; i++)
	{
		if (!(file >> node && file >> neighbour && file >> cost))
		{
			file.close();
			throw 4;
		}
		add_neighbour(node, neighbour, cost);
	}

	if (size_ < 1 || starting_node_ < 0 || starting_node_ >= size_)
	{
		file.close();
		throw 4;
	}

	file.close();
}


List<Neighbour> & ListGraph::operator [] (ulint index)
{
	return adjacency_list_[index];
}

void ListGraph::generate_random(ulint size, double density)
{
	size_ = size;
	starting_node_ = random((ulint)0, size_ - 1);
	ulint edges = density * size_*(size_ - 1) / 2;
	if (predecessors != NULL)
		delete[] predecessors;
	predecessors = new ulint[size_];
	if (shortest_paths != NULL)
		delete[] shortest_paths;
	shortest_paths = new ulint[size_];
	if (adjacency_list_ != NULL)
		delete[] adjacency_list_;
	adjacency_list_ = new List<Neighbour>[size_];

	for (int i = 0; i < size_; i++)
	{
		ulint node = 0, neighbour = 0, cost = random((ulint)1, size_);
		do {
			node = random((ulint)0, size_ - 1);
			neighbour = random((ulint)0, size_ - 1);
		} while (node == neighbour && listContains(node, neighbour));
		add_neighbour(node, neighbour, cost);
		add_neighbour(neighbour, node, cost);
	}
}

void ListGraph::solve_dijkstra()
{
	// element's data is node's number,
	// element's key is node's path cost from starting node
	HeapQueue<int> nonVisited;

	// element's index is node's number,
	// element's value is node's index on heap
	ulint * indices = new ulint[size_];

	// filling the heap
	for (ulint i = 0; i < size_; i++)
	{
		nonVisited.push(i, INF);
		shortest_paths[i] = INF;
		predecessors[i] = INF;
	}

	// obtaining indices from heap
	getIndices(nonVisited, indices);

	// setting starting node's path cost as 0
	// the heap automatically recovers
	nonVisited.set_item_key(indices[starting_node_], 0);

	while (nonVisited.size() > 0)
	{
		ulint currentCost = nonVisited.get_key(0);
		ulint currentNumber = nonVisited.pop_front();
		getIndices(nonVisited, indices);

		for (Neighbour neigh : adjacency_list_[currentNumber])
		{
			if (nonVisited.contains(neigh.number) &&
				nonVisited.get_key(indices[neigh.number]) > currentCost + neigh.path_cost)
			{
				nonVisited.set_item_key(indices[neigh.number], currentCost + neigh.path_cost);
				predecessors[neigh.number] = currentNumber;
				getIndices(nonVisited, indices);
			}
		}
		shortest_paths[currentNumber] = currentCost;
	}
}

bool ListGraph::listContains(ulint node, ulint neighbourNumber)
{
	for (ulint i = 0; i < adjacency_list_[node].size(); i++)
		if (adjacency_list_[node][i].number == neighbourNumber)
			return true;

	return false;
}

std::ostream & operator << (std::ostream & out, ListGraph & graph)
{
	for (int i = 0; i < graph.size(); i++)
	{
		out << "(" << i << ")";
		for (list_iterator<Neighbour> it = graph[i].begin(); it != graph[i].end(); it++)
		{
			out << "->(" << (*it).number << ")[" << (*it).path_cost << "]";
		}
		out << std::endl;
	}

	return out;
}