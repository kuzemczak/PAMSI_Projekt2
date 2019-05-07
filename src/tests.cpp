#include "tests.h"

// funkcja testujaca podany algorytm
// algorithm - enum mowiacy, ktory algorytm przetestowac
// sizes - wektor zawierajacy ilosci wierzcholkow, ktore maja byc przetestowane
// densities - wektor zawierajacy gestosci grafow, ktore maja byc przetestowane
// iterations - ilosc probek skladajacych sie na jeden czas
void testGraphAlgorithm(TestedAlgorithm algorithm, const Vector<ulint> & sizes, const Vector<double> & densities, ulint iterations)
{
	std::ofstream file;
	std::string filename;
	filename = "data/";
	if (algorithm == DIJKSTRA)
		filename.append("Dijkstra");
	else if (algorithm == BELLMAN_FORD)
		filename.append("Bellman_Ford");
	filename.append("_test_output.csv");

	file.open(filename, std::ios::out);

	if (!file.is_open())
	{
		std::cout << "Error: testGraphAlgorithm: could not open file " << filename << std::endl;
		throw 3;
	}

	// wektor klas grafow do testowania
	// kazdy w strukturze z nazwa
	Vector<namedGraph> graphs;
	graphs.push_back(namedGraph(new MatrixGraph, "matrix"));
	graphs.push_back(namedGraph(new ListGraph, "list"));

	// licznik porazek dla Bellmana-Forda
	double failRate = 0;

	for (namedGraph & graph : graphs)
	{
		// wypisanie nazwy grafu
		file << graph.name;
		std::cout << graph.name << "\n";

		// wypisanie naglowka tabeli zawierajacego ilosci wierzcholkow
		for (ulint size : sizes)
		{
			file << "," << size;
		}
		file << "\n";

		// iteracja przez wszystkie gestosci
		for (double density : densities)
		{
			file << density * 100 << "%";
			std::cout << density * 100 << "%\n";

			// iteracja przez ilosci wierzcholkow
			for (ulint size : sizes)
			{
				std::cout << " " << size;

				// zmienna na sredni czas z <iterations> probek
				double mean = 0;

				// pozyskiwanie pojedynczych probek <iterations> razy
				for (int i = 0; i < iterations; i++)
				{
					auto t0 = Clock::now(), t1 = Clock::now();
					switch (algorithm)
					{
					case DIJKSTRA:
						// wygenerowanie losowego grafu
						graph->generate_random(size, density);

						// zmierzenie czasu algorytmu
						t0 = Clock::now();
						graph->solve_dijkstra();
						t1 = Clock::now();
						
						if (i % 10 == 0 && !graph->check_solved())
							failRate++;

						// zapisanie probki
						mean += static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count());
						break;
					case BELLMAN_FORD:
						graph->generate_random(size, density, NEGATIVE_EDGES);
						t0 = Clock::now();
						// sprawdzenie, czy algorytm zakonczyl sie sukcesem
						if (graph->solve_bellman_ford())
						{
							failRate++;
						}
						t1 = Clock::now();
						mean += static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count());
						break;
					}
					std::cout << "\r" << i << "   ";
				}
				// usrednienie sumy probek
				mean /= iterations;
				//failRate /= (double)iterations;
				file << "," << mean;
				std::cout << "\nfail rate: " << failRate << "\n";
				failRate = 0;
			}
			file << "\n";
			std::cout << "\n";
		}
		file << "\n\n";
	}

	file.close();
}
