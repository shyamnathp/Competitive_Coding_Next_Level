// C++ Implementation of Kosaraju's algorithm to print all SCCs 
#include <iostream> 
#include <list> 
#include <stack> 
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<int>& dp, vector<bool>& vis)
{
	// Mark as visited 
	vis[node] = true;
	vector<int> bestAdj;

	// Traverse for all its children 
	for (int i = 0; i < adj[node].size(); i++) {
		// If not visited 
		if (!vis[adj[node][i]])
			dfs(adj[node][i], adj, dp, vis);

		if (i != (adj[node].size() - 1))
		{
			bestAdj.push_back(dp[adj[node][i]]);
		}
		else
		{
			bestAdj.push_back(dp[adj[node][i]]);
			dp[node] = dp[node] + *std::max_element(bestAdj.begin(), bestAdj.end());
		}

		// Store the max of the paths 
		//dp[node] = max(dp[node], 1 + dp[adj[node][i]]);
	}

	//cout << node<<" ";
}
 
void addEdgeScc(vector<vector<int>>& adj, int u, int v)
{
	adj[u].push_back(v);
}

class Graph
{
	int V;    // No. of vertices 
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
	visited[v] = true;

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			fillOrder(*i, visited, Stack);

	Stack.push(v);
}

void Graph::printSCCs()
{
	stack<int> Stack;

	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			fillOrder(i, visited, Stack);

	Graph gr = getTranspose();

	for (int i = 0; i < V; i++)
		visited[i] = false;

	int newI = 0;
	vector<int> sccNode(V, 0);
	int count = 0;
	vector<int> sccCount;

	while (Stack.empty() == false)
	{
		int v = Stack.top();
		Stack.pop();

		if (visited[v] == false)
		{
			gr.DFSUtil(v, visited, newI, sccNode, count);
			sccCount.push_back(count);
			++newI;
		}

		count = 0;
	}

	/*for (int i=0;i<sccCount.size();++i)
	{
		cout << i << " " << sccCount[i] << endl;
	}*/

	vector<vector<int>> adjScc(sccCount.size());

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
				addEdgeScc(adjScc, sccNode[j], sccNode[*i]);
			}
		}
	}

	vector<bool> vis(sccCount.size(), false);

	//dp[0] = 1;
	//dp[1] = 2;
	//dp[2] = 4;
	//dp[3] = 1;
	//dp[4] = 1;
	//dp[5] = 3;

	/*for (int i = 0; i < sccCount.size(); ++i)
	{
		dp[i] = sccCount[i]
	}*/

	for (int i = 0; i < sccCount.size(); i++) {
		if (!vis[i])
		{
			dfs(i, adjScc, sccCount, vis);
			//cout << endl;
		}

	}

	int ans = 0;

	for (int i = 0; i < sccCount.size(); i++) {
		ans = max(ans, sccCount[i]);
	}

	cout << ans;
}

int main()
{
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