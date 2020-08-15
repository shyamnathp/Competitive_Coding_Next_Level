#include <iostream>
#include <vector> 
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

// Function to traverse the DAG 
// and apply Dynamic Programming 
// to find the longest path 
void dfs(int node, vector<vector<int>>& adj,vector<int>& dp, vector<bool>& vis, int count, int& count1, bool& k, int& node1)
{
	// Mark as visited 
	if (vis[node] == false)
	{
		vis[node] = true;

		if (adj[node].size() == 0)
		{
		 	count = count + 1;
			dp[node] = count;
			count1 = count;
			return;
		}
		
		count = count + 1;
		dp[node] = count;
		//count1 = 0;
		k = false;

		//if(count1 !=0 )

	}
	else
	{
		//count = count - 1;
		if (count1 != 0)
		{
			//count2 = count1 - dp[node];
			//count1 = count;
			count1 = count + count1 - dp[node];
		}
   		else
			count1 = count;

		node1 = node;
		k = true;
		//dp[node] = count;
		return;
	}

	// Traverse for all its children 
	for (int i = 0; i < adj[node].size(); i++) {

		// If not visited 
		//if (!vis[adj[node][i]])
		//int count1 = count;
		dfs(adj[node][i], adj, dp, vis, count, count1, k, node1);
		if (count1 != 0 && k==true && node1 == node)
		{
			if (i != (adj[node].size() - 1) )
			{
				dp[node] = count1;
				count1 = 0;
				k = false;
				node1 = -1;
			}
			else
			{
				count1 = 0;
				k = false;
				node1 = -1;
			}	
		}
	/*	else if (i == (adj[node].size() - 1) && count1 != 0 && k == false)
		{
				dp[node] = count1;
				count1 = 0;
				k = false;
				node1 = -1;
		}
		*/

		count = dp[node];
		if(node == node1)
			count1 = 0;

		//if (count < count1)
		//	count1 = count;

		//count = max(count, count1);

		// Store the max of the paths 
		//dp[node] = max(dp[node], 1 + dp[adj[node][i]]);
	}
}

// Function to add an edge 
void addEdge(vector<vector<int>>& adj, int u, int v)
{
	adj[u].push_back(v);
}

// Function that returns the longest path 
int findLongestPath(vector<vector<int>>& adj,int n)
{
	// Dp array 
	vector<int> dp(n,0);
	vector<int> final(n, 0);
	int count = 0;
	int count1 = 0;
	int node1 = -1;
	bool k = false;

	// Visited array to know if the node 
	// has been visited previously or not 
	vector<bool> vis(n, false);

	// Call DFS for every unvisited vertex 
	for (int i = 0; i < n; ++i) {
		if (!vis[i])
		{
			std::fill(vis.begin(),vis.end(),false);
			dfs(i, adj, dp, vis, count, count1, k, node1);
		//	dp[i] = count;
			auto it = max_element(std::begin(dp), std::end(dp));
		//	count = 0;
			count1 = 0;
			k = false;
			final[i] = *it;
		}
		cout<<endl;
	}

	int ans = 0;

	// Traverse and find the maximum of all dp[i] 
	for (int i = 0; i < n; ++i) {
		ans = max(ans, final[i]);
	}
	return ans;
}

// Driver Code 
int main()
{
	std::ifstream in("p103.t2.in");

	int n,m;
	in >> n >> m;
	//const int n = 5;
	//auto adj = make_unique<vector<int>>(n);
	//vector<int> adj[5];
	vector<vector<int>> adj(n);

	for (int i = 0; i < m; ++i)
	{
		int u, v;
		in >> u >> v;
		addEdge(adj, u, v);
	}
	

	cout << findLongestPath(adj, n);

	in.close();
	return 0;
}