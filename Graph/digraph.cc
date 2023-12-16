#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <functional>
using namespace std;

class DirectedGraph 
{ 
	int V;
	vector<list<int>> adj;
public:
	DirectedGraph(int V)
	{
		this->V = V; 
		adj = vector<list<int>>(V, list<int>());
	}
	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}

	bool DFSVisit(int k, std::function<bool (int)> execute) {
		if (!execute(k))
			return false;

		list<int> &k_adjacents = this->adj[k];
    	for (int node : k_adjacents) {
			if (!this->DFSVisit(node, execute))
				return false;
    	}
    	return true;
    	// do something
	}

	bool isCyclic()
	{
	    // Student answer
	    for (int i = 0; i < this->adj.size(); i++) {
	    	int seen = 0;
	    	this->DFSVisit(i, [&](int v) {
	    		if (i == v) {
	    			seen++;
	    			if (seen > 1) return false;
	    		}
	    		return true;
	    	});
	    	if (seen > 1) return true;
	    }
	    return false;
	}
};

void test_one() {
	const int size = 8;
	DirectedGraph g(size); 
	int edege[][2] = {{1,6}, {1,2}, {1,4}, {6,2}, {3,0}, {2,7}, {5,1}, {7,0}, {7,4}};

	for(int i = 0; i < size + 1; i++)
		g.addEdge(edege[i][0], edege[i][1]);

	if(g.isCyclic()) 
		cout << "Graph contains cycle" << endl; 
	else
		cout << "Graph doesn't contain cycle" << endl; 
}

int main() {
	test_one();
	return 0;
}