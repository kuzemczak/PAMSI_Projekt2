#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"
#include "HeapQueue.h"
#include "FastEraseVector.h"

#define TO_FILE_AND_COUT

enum graphGenerationOptions
{
	POSITIVE_EDGES,
	NEGATIVE_EDGES
};

class Edge
{
public:
	ulint start;
	ulint end;
	ulint cost;
	Edge(ulint _start = 1000000000, ulint _end = 1000000000, ulint _cost = 0) :
		start(_start),
		end(_end),
		cost(_cost) {}
};

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

	// wczytanie grafu z pliku o podanej nazwie
	void read_file(const std::string & name);

	// metoda generuje graf o zadanych ilosci wierzcholkow
	// i gestosci
	void generate_random(ulint size, 
		double density, 
		graphGenerationOptions options = POSITIVE_EDGES);
	
	// inicjalizacja struktury przechowujacej informacje
	// o wierzcholkach i krawedziach
	virtual void init_container() = 0;

	// Z wektora zawierajacego krawedzie
	// funkcja losuje podana liczbe krawedzi i ich wagi
	// i zapisuje je do grafu
	virtual void randomize_edges(FastEraseVector<Edge> & edgeContainer, 
		ulint numberOfEdges, 
		graphGenerationOptions options) = 0;

	//////////////////////////////////////// Metody algorytmu Dijkstry
	// Czesc wspolna algorytmu Dijkstry
	// dla wszystkich reprezentacji grafu
	// (czyli dla wszystkich klas dziedziczacych po klasie Graph)
	void solve_dijkstra();

	// Wewnetrzna petla algorytmu Dijkstry
	// dla ka¿dej reprezentacji grafu jest inna
	virtual void dijkstra_inner_loop(ulint currentNumber, 
		ulint currentCost, 
		HeapQueue<ulint> & nonVisited, 
		ulint * indices,
		bool * isVisited) = 0;
	//////////////////////////////////////// ~

	//////////////////////////////////////// Metody algorytmy Bellmana-Forda
	virtual int solve_bellman_ford() = 0;
	//////////////////////////////////////// ~

	virtual bool check_solved() = 0;

	ulint size();
	ulint starting_node();
	void toFile(const std::string & s);

	virtual void add_neighbour(ulint nodeNum, ulint neighbourNum, ulint pathCost) = 0;
};

// funkcja odczytuje indeksy elementow z kolejki priorytetowej
// dziala tylko dla typow integerowych
template<typename T>
void getIndices(HeapQueue<T> & heap, ulint * indices)
{
	for (ulint i = 0; i < heap.size(); i++)
	{
		indices[heap[i]] = i;
	}
}

#endif