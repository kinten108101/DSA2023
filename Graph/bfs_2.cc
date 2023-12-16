#include <iostream>
#include <list>
#include <stack>
#include <map>
#include <stack>
#include <utility>
#include <vector>
#include <set>

using namespace std;

class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const &i : adjList)
			cout << " -> " << i;
	}
	void printArray()
	{
		for (auto const &i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx) 
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};

class Graph
{
private:
	int V;
	Adjacency *adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new Adjacency[V];
	}

	Graph(std::vector<std::vector<int>> &adjacency_list) {
		this->V = 512;
		adj = new Adjacency[this->V];
		std::set<std::pair<int, int>> added_edges;
		for (unsigned int i = 0; i < adjacency_list.size(); i++) {
			std::vector<int> adjacents = adjacency_list[i];
			
				for (int node : adjacents) {
					if (added_edges.find(std::make_pair(i, node)) != added_edges.end()) continue;
					this->addEdge(i, node);
					added_edges.insert(std::make_pair(i, node));
				}

		}
	}
	
	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}
	
    void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "Adjacency list of vertex " << v << "\nhead ";
			adj[v].print();
			cout << endl;
		}
	}
	
	Adjacency *BFS(int v)
    {
    	Adjacency *out_buffer = new Adjacency();
        list<int> buffer;
        std::map<int, bool> visited;

        buffer.push_back(v);
        visited[v] = true;
        Adjacency &init_adjacent_nodes = this->adj[v];
        for (int i = 0; i < init_adjacent_nodes.getSize(); i++) {
        	int node = init_adjacent_nodes.getElement(i);
        	buffer.push_back(node);
        	visited[node] = true;
        }


        // visit
        while (!buffer.empty()) {
        	int k = buffer.front();
        	Adjacency &k_adjacents = this->adj[k];
        	for (int i = 0; i < k_adjacents.getSize(); i++) {
        		int node = k_adjacents.getElement(i);
        		if (visited.find(node) == visited.end()) {
        			visited[node] = true;
        			buffer.push_back(node);
        		} else {

        		}
        	}
        	// do something
        	out_buffer->push(k);

        	buffer.erase(buffer.begin());
        }

        return out_buffer;
	}

	void DFSVisit(int k, std::set<int> &visited, Adjacency *out_buffer = nullptr) {
		visited.insert(k);

		// do something
		if (out_buffer)
		    out_buffer->push(k);

		Adjacency &k_adjacents = this->adj[k];
    	for (int i = 0; i < k_adjacents.getSize(); i++) {
    		int node = k_adjacents.getElement(i);
    		if (visited.find(node) == visited.end()) {
    			this->DFSVisit(node, visited, out_buffer);
    		} else {

    		}
    	}
	}

	Adjacency *DFSRecursive(int v)
    {
        Adjacency *out_buffer = new Adjacency();
        std::set<int> visited;

        this->DFSVisit(v, visited, out_buffer);

        return out_buffer;
	}

	Adjacency *DFSIterative(int v)
    {
        Adjacency *out_buffer = new Adjacency();
        std::stack<int> buffer;
        std::set<int> visited;

        buffer.push(v);

        while (!buffer.empty()) {
        	int k = buffer.top();
        	if (visited.find(k) != visited.end()) {
        		buffer.pop();
        		continue;
        	}

        	// do something
        	out_buffer->push(k);

        	buffer.pop();
        	visited.insert(k);

        	Adjacency &k_adjacents = this->adj[k];
        	for (int i = k_adjacents.getSize() - 1; i >= 0; i--) {
        		int node = k_adjacents.getElement(i);
        		if (visited.find(node) == visited.end()) {
        			buffer.push(node);
        		}
        	}
        }

        return out_buffer;
	}

	Adjacency *DFS(int v)
    {
        //return this->DFSRecursive(v);
        return this->DFSIterative(v);
	}

	void topologicalSortStack() {

	}

	void topologicalSortRecursive() {

	}

	void topologicalSort() {

	}
};

int connectedComponents(vector<vector<int>>& edges) {
    int max = edges.size() - 1;
    Graph graph(edges);
    
    std::set<int> visited;
    int num = 0;
    
    for (int i = 0; i <= max; i++) {
        if (visited.find(i) == visited.end()) {
            num++;
        }
        graph.DFSVisit(i, visited);
    }
    
    return num;
}

void test_dfs() {
	std::cout << "> dfs" << std::endl;
	int V = 8, visited = 0;

	Graph g(V);
	Adjacency *arr;
	int edge[][2] = {{0,1}, {0,2}, {0,3}, {0,4}, {1,2}, {2,5}, {2,6}, {4,6}, {6,7}};
	for(int i = 0; i < 9; i++)
	{
		g.addEdge(edge[i][0], edge[i][1]);
	}

	g.printGraph();
	arr = g.DFS(visited);
	arr->printArray();
	std::cout << std::endl;
	delete arr;
}

void test_connected_graph() {
	std::cout << "> connected-graph" << std::endl;
	std::vector<std::vector<int>> graph {
		{1},
		{0, 2},
		{1, 3},
		{2},
		{}
	};
	std::cout << connectedComponents(graph) << std::endl;
}

int main() {
	test_dfs();
	test_connected_graph();
	return 0;
}