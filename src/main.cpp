#include <iostream>
#include <chrono>
//#include "Node.h"
//#include "HeapQueue.h"
//#include "Vector.h"
#include "Matrix.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Dijkstra.h"
#include "tests.h"


int main()
{
	/*double density = 0.5;
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
		ListGraph graph0, graph1;
		MatrixGraph graph2, graph3;
		graph0.generate_random(10, 0.5);
		graph1.generate_random(10, 0.5);
		graph2.generate_random(10, 0.5);
		graph3.generate_random(10, 0.5);
		//graph.generate_random(10, 0.5);
		std::cout << "graph0:\n" << graph0 << std::endl;
		std::cout << "graph1:\n" << graph1 << std::endl;
		std::cout << "graph2:\n" << graph2 << std::endl;
		std::cout << "graph3:\n" << graph3 << std::endl;
		//Dijkstra(graph0);
		auto t0 = Clock::now();
		graph0.solve_dijkstra();
		auto t1 = Clock::now();
		graph1.solve_bellman_ford();
		auto t2 = Clock::now();
		graph2.solve_dijkstra();
		auto t3 = Clock::now();
		graph3.solve_bellman_ford();
		auto t4 = Clock::now();
		ulint time0 = static_cast<ulint>(std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count()),
			time1 = static_cast<ulint>(std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()),
			time2 = static_cast<ulint>(std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count()),
			time3 = static_cast<ulint>(std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count());
		std::cout << "\nList Dijkstra result:\ntime: " << time0 << " us\n";
		graph0.toFile("data/Dijkstra_result.txt");
		std::cout << "\nList Bellman-Ford result:\ntime: " << time1 << " us\n";
		graph1.toFile("data/Bellman_Ford_result.txt");
		std::cout << "\nMatrix Dijkstra result:\ntime: " << time2 << " us\n";
		graph2.toFile("data/Dijkstra_result.txt");
		std::cout << "\nMatrix Bellman-Ford result:\ntime: " << time3 << " us\n";
		graph3.toFile("data/Bellman_Ford_result.txt");

	} while (getchar() == '\n');*/

	Vector<ulint> sizes;
	Vector<double> densities;
	sizes.push_back(10);
	sizes.push_back(50);
	sizes.push_back(100);
	sizes.push_back(500);
	sizes.push_back(1000);
	densities.push_back(0.25);
	densities.push_back(0.5);
	densities.push_back(0.75);
	densities.push_back(1);

	//testDijkstra(sizes, densities, 10);
	testDijkstra(sizes, densities, 100);
	std::cout << "finish\n";

	getchar();
	return 0;
}