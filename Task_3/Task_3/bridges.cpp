
#include<iostream> 
#include <list> 
#include <algorithm>
#include <fstream>
#include <sstream>

#define NIL -1 
using namespace std;


class Graph
{
	int V;    // No. of vertices 
	list<int> *adj;    // A dynamic array of adjacency lists 
	void bridgeUtil(int v, bool visited[], int disc[], int low[],
		int parent[], int &count);
public:
	Graph(int V);   // Constructor 
	void addEdge(int v, int w);   // to add an edge to graph 
	void bridge();    // prints all bridges 
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);  // Note: the graph is undirected 
}

void Graph::bridgeUtil(int u, bool visited[], int disc[],int low[], int parent[], int &count)
{
	static int time = 0;

	// Mark the current node as visited 
	visited[u] = true;

	// Initialize discovery time and low value 
	disc[u] = low[u] = ++time;

	// Go through all vertices aadjacent to this 
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;  // v is current adjacent of u 

		// If v is not visited yet, then recur for it 
		if (!visited[v])
		{
			parent[v] = u;
			bridgeUtil(v, visited, disc, low, parent, count);

			low[u] = min(low[u], low[v]);

			if (low[v] > disc[u])
			{
				++count;
			//	cout << u << " " << v << endl;
			}
		}

		// Update low value of u for parent function calls. 
		else if (v != parent[u])
			low[u] = min(low[u], disc[v]);
	}

}

void Graph::bridge()
{
	// Mark all the vertices as not visited 
	int count = 0;
	bool *visited = new bool[V];
	int *disc = new int[V];
	int *low = new int[V];
	int *parent = new int[V];

	// Initialize parent and visited arrays 
	for (int i = 0; i < V; i++)
	{
		parent[i] = NIL;
		visited[i] = false;
	}

	// Call the recursive helper function to find Bridges 
	// in DFS tree rooted with vertex 'i' 
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			bridgeUtil(i, visited, disc, low, parent, count);
	//printing count
	cout << count<<endl;
}

int main()
{
	//std::ifstream in("p103.t2.in");

	int ver, edges;
	cin >> ver >> edges;
	Graph g1(ver);

	for (int i = 0; i < edges; ++i)
	{
		int x, y;
		cin >> x >> y;
		g1.addEdge(x, y);
	}
	g1.bridge();

	return 0;
}