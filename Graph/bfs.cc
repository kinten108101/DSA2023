#include <vector>

#include <iostream>
#include "../Utils/utils.h"

std::vector<int> visited;

void bfs(std::vector<std::vector<int>> graph, int start) {
	for (int entry : visited) {
		if (start == entry) return;
	}
	std::vector<int> row = graph[start];
	for (int column_idx : row) {
		std::cout <<  " " << column_idx;
	}
	visited.push_back(start);
	// mark this row visited
	for (int column_idx : row) {
		bfs(graph, column_idx);
	}	
}

int main() {
	utils::runtest("bfs", {
		[]() {
			int init_graph[10][10] = { 
				{0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
			    {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
			    {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
			    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
			    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
			    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
			    {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
			    {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
			    {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
			    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0} };
			int n = 10;
			std::vector<std::vector<int>> graph(n, std::vector<int>());
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					if (init_graph[i][j]) graph[i].push_back(j);
				}
			}

			bfs(graph, 0);
			return 0;
		},
	});
	return 0;
}