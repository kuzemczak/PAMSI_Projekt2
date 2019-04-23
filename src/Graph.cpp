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