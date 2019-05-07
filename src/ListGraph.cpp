#include <fstream>

#include "ListGraph.h"


ListGraph::ListGraph()
{
	adjacency_list_ = NULL;
}


ListGraph::~ListGraph()
{
	delete[] adjacency_list_;
}

void ListGraph::init_container()
{
	if (adjacency_list_ != NULL)
		delete[] adjacency_list_;
	adjacency_list_ = new List<Neighbour>[size_];
}

void ListGraph::add_neighbour(ulint nodeNum, ulint neighbourNum, ulint pathCost)
{
	adjacency_list_[nodeNum].push_front(Neighbour(neighbourNum, pathCost));
}

List<Neighbour> & ListGraph::operator [] (ulint index)
{
	return adjacency_list_[index];
}

void ListGraph::randomize_edges(FastEraseVector<Edge> & edgeContainer, ulint numberOfEdges, graphGenerationOptions options)
{

	for (int i = 0; i < numberOfEdges; i++)
	{
		int cost = 0;
		do {
			if (options == POSITIVE_EDGES)
				cost = random(1, size_);
			else
				cost = random(-size_, size_);
		} while (cost == 0);
		Edge e(edgeContainer.erase(random((ulint)0, edgeContainer.size() - 1)));
		add_neighbour(e.start, e.end, cost);
		add_neighbour(e.end, e.start, cost);
	}
}

void ListGraph::dijkstra_inner_loop(
	ulint currentNumber,
	ulint currentCost,
	HeapQueue<ulint> & nonVisited,
	ulint * indices,
	bool * isVisited)
{
	// przeszukanie sasiadow i zaktualizowanie ich sciezek
	for (Neighbour neigh : adjacency_list_[currentNumber])
	{
		// jesli sasiad nieodwiedzony i jego koszt wiekszy niz
		// sciezki prowadzacej przez sciagniety element
		if (!isVisited[neigh.number] &&
			nonVisited.get_key(indices[neigh.number]) > currentCost + neigh.path_cost)
		{
			// zaktualizuj koszt sasiada
			nonVisited.set_item_key(indices[neigh.number], currentCost + neigh.path_cost);

			// ustaw poprzednika sasiada na element sciagniety
			predecessors[neigh.number] = currentNumber;
			getIndices(nonVisited, indices);
		}
	}
}

int ListGraph::solve_bellman_ford()
{
	for (ulint i = 0; i < size_; i++)
	{
		shortest_paths[i] = INF;
		predecessors[i] = INF;
	}

	shortest_paths[starting_node_] = 0;

	for (ulint i = 0; i < size_ - 1; i++)
	{
		for (ulint j = 0; j < size_; j++)
		{
			for (Neighbour n : adjacency_list_[j])
			{
				if (shortest_paths[n.number] > n.path_cost + shortest_paths[j])
				{
					shortest_paths[n.number] = n.path_cost + shortest_paths[j];
					predecessors[n.number] = j;
				}
			}
		}
	}
	
	return !check_solved();
}

bool ListGraph::check_solved()
{
	for (ulint j = 0; j < size_; j++)
	{
		for (Neighbour n : adjacency_list_[j])
		{
			if (shortest_paths[n.number] > n.path_cost + shortest_paths[j])
			{
				return false;
			}
		}
	}
	return true;
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
		out << "((" << i << "))";
		for (list_iterator<Neighbour> it = graph[i].begin(); it != graph[i].end(); it++)
		{
			out << "--" << (*it).path_cost << "-->(" << (*it).number << ")";
		}
		out << std::endl;
	}

	return out;
}