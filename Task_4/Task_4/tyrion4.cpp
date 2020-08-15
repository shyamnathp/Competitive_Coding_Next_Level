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
#include <bitset>

using namespace std;

bool IsOdd(int i) {

	int k = (i % 2);
	if ((k == 1) || (k == -1))
	{
		return k;
	}
}

void gauss(vector < bitset<2001> >& a, int n, bitset<2001>& ans) {
	vector<int> where(2001, -1);
	for (int col = 0, row = 0; col < 2001 && row < n; ++col) {
		for (int i = row; i < n; ++i)
			if (a[i][col]) {
				swap(a[i], a[row]);
				break;
			}
		if (!a[row][col])
			continue;
		where[col] = row;

		for (int i = 0; i < n; ++i)
			if (i != row && a[i][col])
				a[i] ^= a[row];
		++row;
	}
	// The rest of implementation is the same as above

	//ans.assign(m, 0);
	ans.reset();
	for (int i = 0; i < 2001; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][2000] / a[where[i]][i];

}

int main() {

	//std::ifstream in("p103.t2.in");

	int n;
	cin >> n;

	vector<vector<string>> houses(n);
	//set<string> unq;
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
			if (word != "odd" && word != "even" && unqOne.size() != n)
			{
				index = unqOne.size();
				unqOne.insert({ word, index });
				//++index;
			}
		}

		houses[j] = setTemp;
	}

	vector<int> line(n, 0);
	//vector< vector<int> > A(n, line);

	vector<bitset<2001>> A(n,0);

	int i1 = 0, j1 = 0;
	for (auto it1 = houses.begin(); it1 != houses.end(); it1++, ++i1)
	{
		for (auto it = it1->begin(); it != prev(it1->end()); ++it, ++j1)
		{
			j1 = unqOne[*it];
			//A[i1][j1] = 1;
			A[i1].set(j1);
		}
	}

	//bitset<2000> rhs;
	i1 = 0;
	for (auto it1 = houses.begin(); it1 != houses.end(); it1++, ++i1)
	{
		if (*(prev(it1->end())) == "odd")
		{
			A[i1].set(2000);
		}
		else
		{
			A[i1].reset(2000);
		}
	}

	bitset<2001> ans;
	gauss(A, n, ans);

	cout << ans.count();
}