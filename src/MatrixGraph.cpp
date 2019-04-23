#include "MatrixGraph.h"

#include <fstream>

/*thread_local std::mt19937 gen{ std::random_device{}() };

template<typename T>
T random(T min, T max) {
	return std::uniform_int_distribution<T>{min, max}(gen);
}*/


MatrixGraph::MatrixGraph()
{
	adjacency_matrix_ = NULL;
}

MatrixGraph::~MatrixGraph()
{

}

void MatrixGraph::read_file(const std::string & name)
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
	if (predecessors != NULL)
		delete[] predecessors;
	predecessors = new ulint[size_];
	if (shortest_paths != NULL)
		delete[] shortest_paths;
	shortest_paths = new ulint[size_];
	if (adjacency_matrix_ != NULL)
		delete[] adjacency_matrix_;
	adjacency_matrix_ = new Matrix<ulint>(node, node);
	adjacency_matrix_->zeros();

	for (int i = 0; i < edges; i++)
	{
		if (!(file >> node && file >> neighbour && file >> cost))
		{
			file.close();
			throw 4;
		}
		(*adjacency_matrix_)[node][neighbour] = cost;
	}

	if (size_ < 1 || starting_node_ < 0 || starting_node_ >= size_)
	{
		file.close();
		throw 4;
	}

	file.close();
}

Vector<ulint> & MatrixGraph::operator[] (ulint index)
{
	return (*adjacency_matrix_)[index];
}

void MatrixGraph::generate_random(ulint size, double density)
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
	if (adjacency_matrix_ != NULL)
		delete[] adjacency_matrix_;
	adjacency_matrix_ = new Matrix<ulint>(size_, size_);
	adjacency_matrix_->zeros();

	for (int i = 0; i < size_; i++)
	{
		ulint node = 0, neighbour = 0, cost = random((ulint)1, size_);
		do {
			node = random((ulint)0, size_ - 1);
			neighbour = random((ulint)0, size_ - 1);
		} while (node == neighbour && (*adjacency_matrix_)[node][neighbour] == 0);
		(*adjacency_matrix_)[node][neighbour] = cost;
		(*adjacency_matrix_)[neighbour][node] = cost;
	}
}

void MatrixGraph::solve_dijkstra()
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
	
		for (ulint i = 0; i < size_; i++)
		{
			if ((*adjacency_matrix_)[currentNumber][i] != 0 && nonVisited.contains(i) &&
				nonVisited.get_key(indices[i]) > currentCost + (*adjacency_matrix_)[currentNumber][i])
			{
				nonVisited.set_item_key(indices[i], currentCost + (*adjacency_matrix_)[currentNumber][i]);
				predecessors[i] = currentNumber;
				getIndices(nonVisited, indices);
			}
		}
		shortest_paths[currentNumber] = currentCost;
	}

	delete[] indices;
}

void MatrixGraph::solve_bellman_ford()
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
			for (ulint k = 0; k < size_; k++)
			{
				if ((*adjacency_matrix_)[j][k] != 0 && 
					shortest_paths[k] > (*adjacency_matrix_)[j][k] + shortest_paths[j])
				{
					shortest_paths[k] = (*adjacency_matrix_)[j][k] + shortest_paths[j];
					predecessors[k] = j;
				}
			}
		}
	}
}

std::ostream & operator << (std::ostream & out, MatrixGraph & graph)
{
	out << "____";
	for (int i = 0; i < graph.size(); i++)
		out << "\t|_" << i << "__";
	out << std::endl;
	for (int i = 0; i < graph.size(); i++)
	{
		out << i;
		for (ulint el : graph[i])
		{
			out << "\t|" << el;
		}
		out << std::endl;
	}

	return out;
}

