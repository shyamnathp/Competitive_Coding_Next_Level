
#include<iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>
#include <fstream>

using namespace std;

typedef  pair<int, int> iPair;

struct Graph
{
	int V, E;
	vector< pair<int, iPair> > edges;

	// Constructor 
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}

	void addEdge(int u, int v, int w)
	{
		edges.push_back({ w, {u, v} });
	}

	void kruskalMST(int,int);
};

//Union find algorithm to find cycles
struct DisjointSets
{
	int *parent, *rnk;
	int n;

	// Constructor. 
	DisjointSets(int n)
	{
		this->n = n;
		parent = new int[n + 1];
		rnk = new int[n + 1];

		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;
			parent[i] = i;
		}
	}

	int find(int u)
	{
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	void merge(int x, int y)
	{
		x = find(x), y = find(y);

		if (rnk[x] > rnk[y])
			parent[y] = x;
		else 
			parent[x] = y;

		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};


void Graph::kruskalMST(int V, int k)
{
	multiset<int, std::greater<int>> We;

	// Sort edges in increasing order on basis of cost 
	sort(edges.begin(), edges.end());

	DisjointSets ds(V);

	vector< pair<int, iPair> >::iterator it;
	int count = 0;
	for (it = edges.begin(); it != edges.end() && count < V; it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find(u);
		int set_v = ds.find(v);

		if (set_u != set_v)
		{
			//print the edges in mst
			//cout << u << " - " << v << " " <<it->first<< endl;

			We.insert(it->first);
			ds.merge(set_u, set_v);
			++count;
		}
	}

	multiset<int, std::greater<int>>::iterator it1 = We.begin();
	std::advance(it1,k-2);
	cout << *it1 << endl;

}

int main()
{
	//std::ifstream in("p103.t2.in");
	int V, k, E;
	cin >> V >> k >> E;
	Graph g(V, E);

	for (int i = 0; i < E; ++i)
	{
		int x, y, w;
		cin >> x >> y >> w;
		g.addEdge(x, y, w);
	}

	g.kruskalMST(V,k);

	return 0;
}