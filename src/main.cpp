#include <iostream>
#include <chrono>
//#include "Node.h"
//#include "HeapQueue.h"
//#include "Vector.h"
#include "Matrix.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Dijkstra.h"

typedef std::chrono::high_resolution_clock Clock;


int main()
{
	double density = 0.5;
	int nodes = 10;
	int edges = density * nodes*(nodes - 1) / 2;

	std::ofstream file;
	file.open("data/graph.txt", std::ios::out);

	if (!file.is_open())
		throw 3;

	file << 2*edges << " " << nodes << " " << random(0, nodes - 1) << std::endl;
	for (int i = 0; i < edges; i++)
	{
		int start = -1, end = -1, cost;

		while (start == end)
		{
			start = random(0, nodes - 1);
			end = random(0, nodes - 1);
		}
		cost = random(1, 10);
		file << start << " " << end << " " << cost << std::endl
			<< end << " " << start << " " << cost << std::endl;
	}
	file.close();
	do {
		MatrixGraph graph0, graph1;
		graph0.read_file("data/graph.txt");
		graph1.read_file("data/graph.txt");
		//graph.generate_random(10, 0.5);
		std::cout << "graph0:\n" << graph0 << std::endl;
		std::cout << "graph1:\n" << graph1 << std::endl;
		//Dijkstra(graph0);
		//auto t1 = Clock::now();
		graph0.solve_dijkstra();
		graph1.solve_bellman_ford();
		//auto t2 = Clock::now();
		//ulint time = static_cast<ulint>(std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count());
		std::cout << "\nDijstra result:\n";
		graph0.toFile("data/Dijkstra_result.txt");
		std::cout << "\nBellman-Ford result:\n";
		graph1.toFile("data/Bellman_Ford_result.txt");

	} while (getchar() == '\n');

	return 0;
}