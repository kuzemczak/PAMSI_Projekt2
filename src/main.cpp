#include <iostream>

//#include "Node.h"
//#include "HeapQueue.h"
//#include "Vector.h"
//#include "Matrix.h"
//#include "List.h"
//#include "randutils.hpp"
#include "Graph.h"
#include "Dijkstra.h"

/*thread_local std::mt19937 gen{ std::random_device{}() };

template<typename T>
T random(T min, T max) {
	return std::uniform_int_distribution<T>{min, max}(gen);
}*/

int main()
{
	/*HeapQueue<int> q;

	for (int i = 0; i < 10; i++)
	{
		q.push(random(0, 20));

		for (int j = 0; j <= i; j++)
			std::cout << q[j] << " ";
		std::cout << std::endl;
	}
	std::cout << "hehe\n";

	for (int i = 0; i < 10; i++)
	{
		std::cout << q.pop_front() << " ";
	}

	std::cout << std::endl;*/
	Graph graph;

	if (UINT_MAX < 0)
		std::cout << "smaller\n";
	else
		std::cout << "bigger\n";
	graph.read_file("data/graph.txt");
	std::cout << graph;
	Dijkstra(graph);

	getchar();

	return 0;
}