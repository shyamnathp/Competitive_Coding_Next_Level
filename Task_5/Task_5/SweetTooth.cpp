#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
#include <iterator>
#include <cmath>
#include <set>
#include <vector>
#include <numeric>
#include <stack>

using namespace std;

int make_space(int person, int candy, vector<vector<int>>& assigned, vector<int>& dif_sweets, vector<vector<int>>& dist, int s_c, int count, vector<vector<int>>& total_prefs)
{
	int k = s_c;
	int t = dif_sweets.size();
	for (int j = 0; (j < t) && (s_c != 0); ++j)
	{
		if (j == candy)
		{
			continue;
		}

		if (total_prefs[person][j] <= count)
		{
			if (dif_sweets[j] >= s_c)
			{
				dif_sweets[j] = dif_sweets[j] - s_c;
				dist[person][j] = dist[person][j] + s_c;
				//dist[person][candy] = dist[person][candy] - s_c;
				assigned[j].push_back(person);
				s_c = 0;
			}
			else if (dif_sweets[j] > 0)
			{
				dist[person][j] = dist[person][j] + dif_sweets[j];
			    s_c = s_c - dif_sweets[j];
				dif_sweets[j] = 0;
				assigned[j].push_back(person);
			}
		}
	}

	dist[person][candy] = dist[person][candy] - (k - s_c);
	dif_sweets[candy] = dif_sweets[candy] + (k - s_c);

	return (k-s_c);
}

int try_assign(int person, int candy, vector<vector<int>>& assigned, vector<int>& dif_sweets, vector<vector<int>>& dist, int s_c, int count, vector<vector<int>>& total_prefs)
{
	int k = 0;
	if (dif_sweets[candy] >= s_c)
	{
		//dif_sweets[candy] = dif_sweets[candy] - s_c;
		//dist[person][candy] = s_c;
		//assigned[candy].push_back(person);
		return s_c;
	}
	else
	{
		int toAssign = s_c - dif_sweets[candy];
		//dist[person][candy] = dif_sweets[candy];

		if (toAssign)
			k = dif_sweets[candy];

		//dif_sweets[candy] = 0;

		int index = assigned[candy].size();
		while (index != 0)
		{
			int ktemp = 0;
			int new_person = assigned[candy][index-1];
			int toAssignSub = min(dist[new_person][candy], toAssign);
			ktemp = make_space(new_person, candy, assigned, dif_sweets, dist, toAssignSub, count, total_prefs);
			k = k + ktemp;

			if (dist[new_person][candy] == 0)
			{
				assigned[candy].erase(assigned[candy].begin() + index-1);
			}

			if (k == s_c)
				break;

			--index;
		}
	}

	return k;
}

int main()
{
	//std::ifstream in("p103.t2.in");

	int c, t;
	cin >> c;
	cin >> t;

	vector<int> dif_sweets(t);
	int s = 0;
	for (int i = 0; i < t; ++i)
	{
		int temp;
		cin >> temp;
		dif_sweets[i] = temp;
		s = s + temp;
	}

	//all the preferences as a matrix
	vector<vector<int>> total_prefs(c, vector<int>(t));

	vector<int> min_row(c);

	for (int i = 0; i < c; ++i)
	{
		int temp_min = t + 1;
		for (int j = 0; j < t; ++j)
		{
			int temp;
			cin >> temp;
			total_prefs[i][j] = temp;
			temp_min = min(temp_min, temp);
		}
		min_row[i] = temp_min;
	}

	//the candies to be divided to each and smodc is the candies left out
	int s_c = floor(s / c);
	//int smodc = s % c;
	int count = *max_element(min_row.begin(), min_row.end());

	
	while (count != t && count != 0)
	{
		vector<int> diff_sweets = dif_sweets;
		vector<vector<int>> assigned(t);
		vector<vector<int>> dist(c, vector<int>(t));
		bool possible = true;
		int k = 0;

		for (int i = 0; i < c; ++i)
		{
			k = 0;
			for (int j = 0; j < t; ++j)
			{
				if (total_prefs[i][j] <= count)
				{
					int ktemp = try_assign(i, j, assigned, diff_sweets, dist, s_c - k, count, total_prefs);

					if (ktemp > (s_c-k))
					{
						ktemp = s_c - k;
					}

					dist[i][j] = dist[i][j] + ktemp;
					diff_sweets[j] = diff_sweets[j] - ktemp;
					assigned[j].push_back(i);
					k = k + ktemp;
				}

				if (k == s_c)
					break;
			}

			if (k != s_c)
			{
				possible = false;
				break;
			}
			
		}
		
		if (possible)
			break;
		else
			++count;
	}

	cout << count << endl;

	return 0;
}