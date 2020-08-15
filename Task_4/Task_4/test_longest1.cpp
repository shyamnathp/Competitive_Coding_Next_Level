// C++ program to find the longest
// path in the DAG 

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

// Function to traverse the DAG 
// and apply Dynamic Programming 
// to find the longest path 
void dfs(int node, vector<vector<int>>& adj, vector<int>& dp, vector<bool>& vis)
{
	// Mark as visited 
	vis[node] = true;

	// Traverse for all its children 
	for (int i = 0; i < adj[node].size(); i++) {

		vector<int> bestAdj;
		// If not visited 
		if (!vis[adj[node][i]])
			dfs(adj[node][i], adj, dp, vis);

		if (i != (adj[node].size()-1))
		{
			bestAdj.push_back(dp[adj[node][i]]);
		}
		else
		{
			bestAdj.push_back(dp[adj[node][i]]);
			dp[node] = dp[node] + *std::max_element(bestAdj.begin(),bestAdj.end());
		}

		// Store the max of the paths 
		//dp[node] = max(dp[node], 1 + dp[adj[node][i]]);
	}

	//cout << node<<" ";
}

// Function to add an edge 
void addEdge(vector<vector<int>>& adj, int u, int v)
{
	adj[u].push_back(v);
}

// Function that returns the longest path 
int findLongestPath(vector<vector<int>>& adj, int n)
{
	// Dp array 
	vector<int> dp(n, 0);
	//memset(dp, 0, sizeof dp);

	// Visited array to know if the node 
	// has been visited previously or not
	vector<bool> vis(n, false);
	//memset(vis, false, sizeof vis);

	dp[0] = 1;
	dp[1] = 2;
	dp[2] = 4;
	dp[3] = 1;
	dp[4] = 1;
	//dp[5] = 3;

	// Call DFS for every unvisited vertex 
	for (int i = 0; i < n; i++) {
		if (!vis[i])
		{
			dfs(i, adj, dp, vis);
			//cout << endl;
		}

	}

	int ans = 0;

	// Traverse and find the maximum of all dp[i] 
	for (int i = 0; i < n; i++) {
		ans = max(ans, dp[i]);
	}

	//vector<int> largest;
	//findVerticesLongestPath(ans,adj,dp, largest, dp[ans]);
	return ans;
}

// Driver Code 
int main()
{
	std::ifstream in("p103.t2.in");
	int n,m;
	in >> n>>m;
	vector<vector<int>> adj(n);

	// Example-1 
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		in >> u >> v;
		addEdge(adj, u, v);
	}

	cout << findLongestPath(adj, n);
	return 0;
}