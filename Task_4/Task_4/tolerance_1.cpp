
#include <iostream> 
#include <list> 
#include <stack> 
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<int>& dp, vector<bool>& vis)
{
	// Mark as visited 
	vis[node] = true;

	// Traverse for all its children 
	for (int i = 0; i < adj[node].size(); i++) {

		// If not visited 
		if (!vis[adj[node][i]])
			dfs(adj[node][i], adj, dp, vis);

		// Store the max of the paths 
		dp[node] = max(dp[node], 1 + dp[adj[node][i]]);
	}

	//cout << node << " ";
}

void addEdgeScc(vector<vector<int>>& adj, int u, int v)
{
	adj[u].push_back(v);
}

void findVerticesLongestPath(int ans, vector<vector<int>>& adj, vector<int>& dp, vector<int>& maxVer, vector<int>& sccCount)
{
	int high = 0;
	int sccCountLength = 0;

	if (adj[ans].size() == 0)
		return;

	int it = 0;

	for (int i = 0; i < adj[ans].size(); i++) {
		it = max(it, dp[adj[ans][i]]);
	}

	for (int i = 0; i < adj[ans].size(); ++i)
	{
		if (dp[adj[ans][i]] == it && (sccCount[adj[ans][i]] > sccCountLength))
		{
				//	maximo = max(maximo, sccCount[(adj[ans][i])]);
				sccCountLength = sccCount[adj[ans][i]];
				high = adj[ans][i];
		}
	}

	maxVer.push_back(high);
	findVerticesLongestPath(high, adj, dp, maxVer, sccCount);
}


int findLongestPath(vector<vector<int>>& adj, vector<int>& sccCount)
{
	// Dp array 
	vector<int> dp(sccCount.size(), 0);
	
	vector<bool> vis(sccCount.size(), false);
	
	for (int i = 0; i < sccCount.size(); i++) {
		if (!vis[i])
		{
			dfs(i, adj, dp, vis);
			//cout << endl;
		}

	}

	int ans = 0;

	
	for (int i = 0; i < sccCount.size(); i++) {
		ans = max(ans, dp[i]);
	}


	vector<int> longer;
	for (int j = 0; j < sccCount.size(); j++)
	{
		if (ans == dp[j])
		{
			vector<int> maxVer;
			maxVer.push_back(j);
			findVerticesLongestPath(j, adj, dp, maxVer, sccCount);

			int longest = 0;
			for (int i = 0; i < maxVer.size(); ++i)
			{
				longest = longest + sccCount[maxVer[i]];
			}

			//longest = longest + dp[ans];
			longer.push_back(longest);
		}
	}

	auto it = max_element(std::begin(longer), std::end(longer));

	return *it;


}

class Graph
{
	int V;   
	list<int> *adj;    // An array of adjacency lists 

	void fillOrder(int v, bool visited[], stack<int> &Stack);
	void DFSUtil(int v, bool visited[], int newI, vector<int>& sccNode, int& count);
public:
	Graph(int V);
	void addEdge(int v, int w);

	void printSCCs();

	Graph getTranspose();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}


void Graph::DFSUtil(int v, bool visited[], int newI, vector<int>& sccNode, int& count)
{
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
			gr.DFSUtil(v, visited, newI, sccNode, count);
		//	cout << endl;
			sccCount.push_back(count);
			++newI;
		}

		count = 0;
	}

	/*for (int i=0;i<sccCount.size();++i)
	{
		cout << i << " " << sccCount[i] << endl;
	}*/

	//converting Graph to SCCGraph

	vector<vector<int>> adjScc(sccCount.size());

	for (int j = 0; j < V; ++j)
	{
		list<int>::iterator i;
		for (i = adj[j].begin(); i != adj[j].end(); ++i)
		{
			//g.adj[*i].push_back(v);
			if (sccNode[j] != sccNode[*i])
			{
				//cout << sccNode[j] << " " << sccNode[*i] << endl;
				addEdgeScc(adjScc, sccNode[j], sccNode[*i]);
			}
		}
	}

	cout << findLongestPath(adjScc, sccCount);

}

// Driver program to test above functions 
int main()
{
	// Create a graph given in the above diagram 

	//std::ifstream in("p103.t2.in");
	
	int n, m;
	cin >> n >> m;
	Graph g(n);

	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		g.addEdge(u, v);
	}

	g.printSCCs();

	return 0;
}