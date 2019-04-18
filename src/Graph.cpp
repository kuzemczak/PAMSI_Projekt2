#include <fstream>

#include "Graph.h"

Graph::Graph()
{
	starting_node_ = -1;
	size_ = 0;
	adjacency_list_ = NULL;
}


Graph::~Graph()
{
}

void Graph::add_neighbour(ulint nodeNum, ulint neighbourNum, ulint pathCost)
{
	adjacency_list_[nodeNum].push(Neighbour(neighbourNum, pathCost));
}

void Graph::read_file(const std::string & name)
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

ulint Graph::size()
{
	return size_;
}

ulint Graph::starting_node()
{
	return starting_node_;
}

List<Neighbour> & Graph::operator [] (ulint index)
{
	return adjacency_list_[index];
}

std::ostream & operator << (std::ostream & out, Graph & graph)
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