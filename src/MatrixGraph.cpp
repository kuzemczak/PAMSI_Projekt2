#include "MatrixGraph.h"

#include <fstream>

MatrixGraph::MatrixGraph()
{
	adjacency_matrix_ = NULL;
}

MatrixGraph::~MatrixGraph()
{

}

void MatrixGraph::init_container()
{
	if (adjacency_matrix_ != NULL)
		delete adjacency_matrix_;
	adjacency_matrix_ = new Matrix<ulint>(size_, size_);
	adjacency_matrix_->zeros();
}

Vector<ulint> & MatrixGraph::operator[] (ulint index)
{
	return (*adjacency_matrix_)[index];
}

void MatrixGraph::randomize_edges(FastEraseVector<Edge> & edgeContainer, ulint numberOfEdges, graphGenerationOptions options)
{
	for (ulint i = 0; i < numberOfEdges; i++)
	{
		int cost = 0;
		do {
			if (options == POSITIVE_EDGES)
				cost = random(1, size_);
			else
				cost = random(-size_, size_);
		} while (cost == 0);
		Edge e(edgeContainer.erase(random((ulint)0, edgeContainer.size() - 1)));
		(*adjacency_matrix_)[e.start][e.end] = cost;
		(*adjacency_matrix_)[e.end][e.start] = cost;
	}
}

void MatrixGraph::dijkstra_inner_loop(
	ulint currentNumber, 
	ulint currentCost, 
	HeapQueue<ulint> & nonVisited, 
	ulint * indices,
	bool * isVisited)
{
	// przeszukanie sasiadow i zaktualizowanie ich sciezek
	for (ulint i = 0; i < size_; i++)
	{
		// jesli sasiad nieodwiedzony i jego koszt wiekszy niz
		// sciezki prowadzacej przez sciagniety element
		if ((*adjacency_matrix_)[currentNumber][i] != 0 && !isVisited[i] &&
			nonVisited.get_key(indices[i]) > currentCost + (*adjacency_matrix_)[currentNumber][i])
		{
			// zaktualizuj koszt sasiada
			nonVisited.set_item_key(indices[i], currentCost + (*adjacency_matrix_)[currentNumber][i]);

			// ustaw poprzednika sasiada na element sciagniety
			predecessors[i] = currentNumber;
			getIndices(nonVisited, indices);
		}
	}
}

int MatrixGraph::solve_bellman_ford()
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
	
	return !check_solved();
}

bool MatrixGraph::check_solved()
{
	for (ulint j = 0; j < size_; j++)
	{
		for (ulint k = 0; k < size_; k++)
		{
			if ((*adjacency_matrix_)[j][k] != 0 &&
				shortest_paths[k] >(*adjacency_matrix_)[j][k] + shortest_paths[j])
			{
				return false;
			}
		}
	}
	return true;
}

void MatrixGraph::add_neighbour(ulint nodeNum, ulint neighbourNum, ulint pathCost)
{
	(*adjacency_matrix_)[nodeNum][neighbourNum] = pathCost;
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

