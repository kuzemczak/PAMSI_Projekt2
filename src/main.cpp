#include <iostream>
#include <chrono>

#include "Matrix.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "tests.h"


int main()
{
	//Vector<ulint> sizes;
	//Vector<double> densities;
	//sizes.push_back(100);
	////sizes.push_back(100);
	////densities.push_back(0.25);
	////densities.push_back(0.5);
	////densities.push_back(0.75);
	////densities.push_back(1);
	//for (double i = 0.05; i < 1.01; i += 0.05)
	//{
	//	densities.push_back(i);
	//}
	//
	//testGraphAlgorithm(DIJKSTRA, sizes, densities, 100);
	ListGraph graph;
	graph.read_file("data/graph.txt");
	std::cout << graph;
	graph.solve_dijkstra();
	std::cout << "result: " << graph.check_solved() << std::endl;
	graph.toFile("data/Dijkstra_result.txt");
	std::cout << "finish\n";

	getchar();
	return 0;
}