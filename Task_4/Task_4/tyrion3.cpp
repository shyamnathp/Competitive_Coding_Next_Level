#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <set>
#include <map>
#include <iterator>
#include <list>

using namespace std;

bool IsOdd(int i) {

	int k = (i % 2);
	if ((k == 1) || (k == -1))
	{
		return k;
	}
}

void getCofactor(vector<vector<int>>& A, vector<vector<int>>& temp, int p, int q, int n)
{
	int i = 0, j = 0;

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q)
			{
				temp[i][j++] = A[row][col];

				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}

int determinant(vector<vector<int>>& A, int n)
{
	int D = 0; // Initialize result 

	if (n == 1)
		return A[0][0];

	vector<vector<int>> temp(n, vector<int>(n));  

	int sign = 1; 
	for (int f = 0; f < n; f++)
	{
		getCofactor(A, temp, 0, f, n);
		D += sign * A[0][f] * determinant(temp, n - 1);

		sign = -sign;
	}

	return D;
}

void inverse(vector<vector<int>>& A, vector<vector<int>>& adj, int n)
{
	if (n == 1)
	{
		adj[0][0] = 1;
		return;
	}

	int sign = 1;

	vector<vector<int>> temp(n, vector<int>(n));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			getCofactor(A, temp, i, j, n);

			sign = ((i + j) % 2 == 0) ? 1 : -1;

			adj[j][i] = (sign)*(determinant(temp, n - 1));
		}
	}
}

// Function to calculate and store inverse, returns false if 
// matrix is singular 
/*void inverse(vector<vector<int>>& A, vector<vector<int>>& inverse, int n)
{
	//int det = determinant(A, n);
	vector<vector<int>> adj(n, vector<int>(n));
	adjoint(A, adj, n);

	inverse = std::move(adj);

	// Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
	//for (int i = 0; i < n; i++)
		//for (int j = 0; j < n; j++)
			//inverse[i][j] = adj[i][j] / det;
} */

int main() {

	//std::ifstream in("p103.t2.in");

	int n;
	cin >> n;

	vector<vector<string>> houses(n);
	set<string> unq;
	map<string, int> unqOne;

	cin.ignore(256, '\n');
	//string l;
	//getline(in,l);

	int index = 0;

	for (int j = 0; j < n; ++j)
	{
		string line;
		getline(cin, line);
		istringstream iss(line);
		string word;
		//int oddEven;

		vector<string> setTemp;

		while (iss >> word)
		{
			setTemp.push_back(word);
			if (word != "odd" && word != "even" && unqOne.size() !=n)
			{
				unq.insert(word);
				index = unqOne.size();
				unqOne.insert({ word, index });
				//++index;
			}		
		}

		houses[j]=setTemp;
	}

	vector<int> line(n, 0);
	vector< vector<int> > A(n, line);

	int i1=0, j1 = 0;
	for (auto it1 = houses.begin(); it1 != houses.end(); it1++, ++i1)
	{
		for (auto it = it1->begin(); it != prev(it1->end()); ++it)
		{
			j1 = unqOne[*it];
			A[i1][j1] = 1;
		}
	}

	vector<int> rhs(n);
	i1 = 0;
	for (auto it1 = houses.begin(); it1 != houses.end(); it1++, ++i1)
	{
		if (*(prev(it1->end())) == "odd")
		{
			rhs[i1] = 1;
		}
		else
		{
			rhs[i1] = 0;
		}
	}


	vector<vector<int>> inv(n, vector<int>(n));
	inverse(A, inv, n); //adj = inv since determinant is always -1 or 1

	vector<int> x(n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			x[i] = x[i] + inv[i][j]*rhs[j];
		}
	}

	int mycount = count_if(x.begin(),x.end(), IsOdd);

	cout << mycount;

}