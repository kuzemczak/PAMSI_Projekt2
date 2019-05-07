#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <iostream>
#include <string>

#include "Vector.h"
#include "List.h"
#include "Graph.h"
#include "FastEraseVector.h"

// Klasa pomocnicza - Sasiad
// zawiera numer wierzcholka
// koszt krawedzi do sasiada
class Neighbour
{
public:
	ulint number;
	ulint path_cost;

	Neighbour(ulint num = 1000000000, ulint cost = 0) : number(num), path_cost(cost) {}
};


// Graf reprezentowany za pomoca listy sasiedztwa
class ListGraph : public Graph
{
	// lista sasiedztwa
	// w rzeczywistosci zwykla tablica list jednokierunkowych
	// numer listy w tablicy to numer wierzcholka
	// lista zawiera sasiadow wierzcholka
	List<Neighbour> * adjacency_list_;

	bool listContains(ulint node, ulint neighbourNumber);
public:
	ListGraph();
	~ListGraph();

	// inicjalizacja struktury przechowujacej informacje
	// o wierzcholkach i krawedziach
	// tutaj: adjacency_list_
	void init_container();

	// dodanie sasiada do wskazanego wierzcholka
	void add_neighbour(ulint nodeNum, ulint neighbourNum, ulint pathCost);
	
	// wczytanie grafu z podanego pliku
	//void read_file(const std::string & name);

	// przeciazenie operatora []
	// zwraca liste sasiadow wierzcholka o numerze <index>
	List<Neighbour> & operator [] (ulint index);

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

};

std::ostream & operator << (std::ostream & out, ListGraph & graph);


#endif