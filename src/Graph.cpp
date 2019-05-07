#include "Graph.h"
#include <fstream>


Graph::Graph()
{
	starting_node_ = -1;
	size_ = 0;
	predecessors = NULL;
	shortest_paths = NULL;
}


Graph::~Graph()
{
}

ulint Graph::size()
{
	return size_;
}

ulint Graph::starting_node()
{
	return starting_node_;
}

void Graph::toFile(const std::string & s)
{
	std::ofstream file;
	file.open(s, std::ios::out);
	if (!file.is_open())
		throw 3;

	for (ulint i = 0; i < size_; i++)
	{
		file << i << ": ";
#ifdef TO_FILE_AND_COUT
		std::cout << i << ": ";
#endif
		Vector<ulint> path;
		path.push_back(i);
		while (path[path.size() - 1] != starting_node_ &&
			predecessors[path[path.size() - 1]] < size_)
		{
			path.push_back(predecessors[path[path.size() - 1]]);
		}
		ulint popped = path.pop_back();
		file << popped;
#ifdef TO_FILE_AND_COUT
		std::cout << popped;
#endif
		while (path.size() > 0)
		{
			popped = path.pop_back();
			file << "->" << popped;
#ifdef TO_FILE_AND_COUT
			std::cout << "->" << popped;
#endif
		}
		file << "\t[" << shortest_paths[i] << "]" << std::endl;
#ifdef TO_FILE_AND_COUT
		std::cout << "\t[" << shortest_paths[i] << "]" << std::endl;
#endif
	}
	file.close();
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
	if (predecessors != NULL)
		delete[] predecessors;
	predecessors = new ulint[size_];
	if (shortest_paths != NULL)
		delete[] shortest_paths;
	shortest_paths = new ulint[size_];
	init_container();

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


void Graph::generate_random(ulint size, double density, graphGenerationOptions options)
{
	if (size == 0 || density < 0.001)
	{
		std::cout << "Error: ListGraph::generate_random : zero parameter, shouldn't be.";
		throw 5;
	}

	size_ = size;
	starting_node_ = random((ulint)0, size_ - 1);
	ulint edges = static_cast<ulint>(density * size_*(size_ - 1) / 2);

	// zbior wszystkich mozliwych krawedzi, 
	// sposrod ktorych losowane beda krawedzie w generowanym grafie.
	// Przyspiesza to znacznie generowanie grafu i zapewnia duza losowosc,
	// a takze brak powtarzalnosci.
	FastEraseVector<Edge> randEdges;

	// wypelnienie zbioru krawedzi
	for (ulint i = 0; i < size_; i++)
		for (ulint j = i + 1; j < size_; j++)
		{
			randEdges.push_back(Edge(i, j));
		}

	// inicjalizacja struktur w grafie
	if (predecessors != NULL)
		delete[] predecessors;
	predecessors = new ulint[size_];
	if (shortest_paths != NULL)
		delete[] shortest_paths;
	shortest_paths = new ulint[size_];

	init_container();
	randomize_edges(randEdges, edges, options);
}

void Graph::solve_dijkstra()
{
	// kolejka priorytetowa w postaci kopca
	// najmniejszy klucz na szczycie kopca
	// wartosc elementu to numer wierzcholka,
	// klucz elementu to wartosc sciezki od wierzcholka poczatkowego
	HeapQueue<int> nonVisited;

	// index elementu to numer wierzcholka,
	// wartosc elementu to numer wierzcholka w kolejce
	ulint * indices = new ulint[size_];

	// index elementu to numer wierzcholka
	// wartosc elementu mowi, czy wierzcholek
	// ma wyznaczona najkrotsza sciezke (byl odwiedzony)
	bool * isVisited = new bool[size_];

	// wypelnienie kolejki i zainicjowanie
	// pozostalych struktur
	for (ulint i = 0; i < size_; i++)
	{
		nonVisited.push(i, INF);
		shortest_paths[i] = INF;
		predecessors[i] = INF;
		isVisited[i] = false;
	}

	// uzyskanie indeksow wierzcholkow w kolejce
	getIndices(nonVisited, indices);

	// ustawienie kosztu wierzcholka poczatkowego na 0
	// kopiec automatycznie sie odnawia
	nonVisited.set_item_key(indices[starting_node_], 0);

	// sciaganie elementu ze szczytu kopca
	// czyli elementu z najkrotsza sciezka od elementu startowego
	while (nonVisited.size() > 0)
	{
		// sciagniecie wierzcholka ze szczytu kolejki-kopca
		// i zapisanie jego danych
		ulint currentCost = nonVisited.get_key(0);
		ulint currentNumber = nonVisited.pop_front();

		// ustawienie sciagnietego elementu jako odwiedzony
		isVisited[currentNumber] = true;
		getIndices(nonVisited, indices);

		// przeszukanie sasiadow i zaktualizowanie ich sciezek
		dijkstra_inner_loop(currentNumber, currentCost, nonVisited, indices, isVisited);
		
		// ustawienie kosztu sciagnietego elementu jako najmniejszego
		// dla tego elementu
		shortest_paths[currentNumber] = currentCost;
	}
	delete[] indices;
	delete[] isVisited;
}