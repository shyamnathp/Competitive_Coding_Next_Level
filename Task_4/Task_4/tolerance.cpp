// C++ Implementation of Kosaraju's algorithm to print all SCCs 
#include <iostream> 
#include <list> 
#include <stack> 
#include <vector>
using namespace std;

class Graph
{
	int V;    // No. of vertices 
	list<int> *adj;    // An array of adjacency lists 

	// Fills Stack with vertices (in increasing order of finishing 
	// times). The top element of stack has the maximum finishing  
	// time 
	void fillOrder(int v, bool visited[], stack<int> &Stack);

	// A recursive function to print DFS starting from v 
	void DFSUtil(int v, bool visited[], int newI, vector<int>& sccNode, int& count);
public:
	Graph(int V);
	void addEdge(int v, int w);

	// The main function that finds and prints strongly connected 
	// components 
	void printSCCs();

	// Function that returns reverse (or transpose) of this graph 
	Graph getTranspose();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

// A recursive function to print DFS starting from v 
void Graph::DFSUtil(int v, bool visited[], int newI, vector<int>& sccNode, int& count)
{
	// Mark the current node as visited and print it 
	++count;
	visited[v] = true;
	//cout << v << " ";
	//cout << "SCC Graph index" << newI;
    sccNode[v] = newI;

	// Recur for all the vertices adjacent to this vertex 
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited, newI, sccNode, count);
}

Graph Graph::getTranspose()
{
	Graph g(V);
	for (int v = 0; v < V; v++)
	{
		// Recur for all the vertices adjacent to this vertex 
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			g.adj[*i].push_back(v);
		}
	}
	return g;
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list. 
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
	// Mark the current node as visited and print it 
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex 
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			fillOrder(*i, visited, Stack);

	// All vertices reachable from v are processed by now, push v  
	Stack.push(v);
}

// The main function that finds and prints all strongly connected  
// components 
void Graph::printSCCs()
{
	stack<int> Stack;

	// Mark all the vertices as not visited (For first DFS) 
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Fill vertices in stack according to their finishing times 
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			fillOrder(i, visited, Stack);

	// Create a reversed graph 
	Graph gr = getTranspose();

	// Mark all the vertices as not visited (For second DFS) 
	for (int i = 0; i < V; i++)
		visited[i] = false;
	
	int newI = 0;
	vector<int> sccNode(V, 0);
	int count = 0;
	vector<int> sccCount;

	// Now process all vertices in order defined by Stack 
	while (Stack.empty() == false)
	{
		// Pop a vertex from stack 
		int v = Stack.top();
		Stack.pop();

		// Print Strongly connected component of the popped vertex 
		if (visited[v] == false)
		{
			gr.DFSUtil(v, visited, newI,sccNode,count);
			cout << endl;
			sccCount.push_back(count);
		}

		++newI;
		count = 0;
	}

	/*for (int i=0;i<sccCount.size();++i)
	{
		cout << i << " " << sccCount[i] << endl;
	}*/

	//converting Graph to SCCGraph

	for (int j = 0; j < V; ++j)
	{
		list<int>::iterator i;
		for (i = adj[j].begin(); i != adj[j].end(); ++i)
		{
			//g.adj[*i].push_back(v);
			if (sccNode[j] != sccNode[*i])
			{
				//cout << sccNode[j] << " " << sccNode[*i] << endl;
			}
		}
	}


}

// Driver program to test above functions 
int main()
{
	// Create a graph given in the above diagram 
	int n=5;
	//cin >> n;
	Graph g(5);
	g.addEdge(1, 0);
	g.addEdge(0, 2);
	g.addEdge(2, 1);
	g.addEdge(0, 3);
	g.addEdge(3, 4);

	cout << "Following are strongly connected components in "
		"given graph \n";
	g.printSCCs();

	return 0;
}