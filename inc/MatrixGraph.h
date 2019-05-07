#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Matrix.h"
#include "HeapQueue.h"
#include "FastEraseVector.h"

// Graf reprezentowany za pomoc¹ macierzy s¹siedztwa
class MatrixGraph : public Graph
{
	// Macierz sasiedztwa
	// zwykla macierz, gdzie
	// numer wiersza to numer wierzcholka
	// numer kolumny to numer sasiada
	// wartosc elementu macierzy to koszt krawedzi
	Matrix<int> * adjacency_matrix_;

public:
	MatrixGraph();
	~MatrixGraph();

	// inicjalizacja struktury przechowujacej informacje
	// o wierzcholkach i krawedziach
	// tutaj: adjacency_matrix_
	void init_container();

	// przeciazenie operatora []
	// zwraca wiersz macierzy
	Vector<ulint> & operator[] (ulint index);

	// Z wektora zawierajacego krawedzie
	// funkcja losuje podana liczbe krawedzi i ich wagi
	// i zapisuje je do grafu
	void randomize_edges(FastEraseVector<Edge> & edgeContainer, 
		ulint numberOfEdges, 
		graphGenerationOptions options);

	// Wewnetrzna petla algorytmu Dijkstry
	// dla ka¿dej reprezentacji grafu jest inna
	void dijkstra_inner_loop(
		ulint currentNumber, 
		ulint currentCost, 
		HeapQueue<ulint> & nonVisited, 
		ulint * indices,
		bool * isVisited);

	// Algorytm Bellmana-Forda - znalezienie najkrotszych drog 
	int solve_bellman_ford();

	bool check_solved();

	void add_neighbour(ulint nodeNum, ulint neighbourNum, ulint pathCost);
};

std::ostream & operator << (std::ostream & out, MatrixGraph & graph);
#endif
