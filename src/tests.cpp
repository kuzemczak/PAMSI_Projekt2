#include "tests.h"

void testDijkstra(const Vector<ulint> & sizes, const Vector<double> & densities, ulint iterations)
{
	std::ofstream file;
	file.open("data/Dijkstra_test_output.csv", std::ios::out);

	if (!file.is_open())
	{
		std::cout << "Error: testDijkstra : could not open file data/Dijkstra_test_output.csv\n";
		throw 3;
	}

	Vector<namedGraph> graphs;
	graphs.push_back(namedGraph(new MatrixGraph, "matrix"));
	graphs.push_back(namedGraph(new ListGraph, "list"));

	for (namedGraph & graph : graphs)
	{
		file << graph.name;
		std::cout << graph.name << "\n";
		for (ulint size : sizes)
		{
			file << "," << size;
		}
		file << "\n";
		for (double density : densities)
		{
			file << density * 100 << "%";
			std::cout << density * 100 << "%";
			for (ulint size : sizes)
			{
				std::cout << " " << size;
				double mean = 0;
				for (int i = 0; i < iterations; i++)
				{
					graph->generate_random(size, density);
					auto t0 = Clock::now();
					graph->solve_dijkstra();
					auto t1 = Clock::now();
					mean += static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count());
				}
				mean /= iterations;
				file << "," << mean;
			}
			file << "\n";
			std::cout << "\n";
		}
		file << "\n\n";
	}
}

void testBellmanFord(Vector<ulint> sizes, Vector<double> densities, ulint iterations)
{

}