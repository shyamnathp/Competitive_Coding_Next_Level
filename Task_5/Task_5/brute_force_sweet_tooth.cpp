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
#include <iomanip>

using namespace std;

int random(int min, int max) //range : [min, max)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

bool distribute(int person, vector<vector<int>>& dist, vector<vector<int>>& prefs, vector<int>& diff_sweets, int& s_c, int t, int value, int smodc);

//move_around is used go back to the previous person who was assigned a sweet, and tries to assign him someother sweet
bool move_around(int person, vector<vector<int>>& dist, vector<vector<int>>& prefs, vector<int>& diff_sweets, int s_c, int t, int value, int s_cMain)
{
	if (dist[person][value] > 0)
	{
		int z1 = min(dist[person][value], s_c);
		int z = z1;
		bool k = distribute(person, dist, prefs, diff_sweets, z, t, value + 1, s_cMain);

		if (z == 0)
		{
			z = z1;
		}

		if (!k)
		{
			return false;
		}
		else
		{
			dist[person][value] = dist[person][value] - z;
			diff_sweets[value] = diff_sweets[value] + z;
			return true;
		}
		//distribute(person, dist, prefs, diff_sweets, s_c, t, value, smodc);
	/*	if (dist[person][i] > 0)
		{

		}
		else
		{
			dist[person][i] = diff_sweets[i];
			s_c = s_c - diff_sweets[i];
			diff_sweets[i] = 0;
		}*/
	}
	else
	{
		if (person != 0)
			move_around(person - 1, dist, prefs, diff_sweets, s_c, t, value, s_cMain);
		else
			return false;
	}

	return true;

}

//trying to distribute the sweets to the person(person1) under consideration. We start from his top priority, if there are no sweets of
//his top priority, we move back to the previous person(person2) who uses that sweet and try to assign that person(person2) to another sweet thus
//making the sweet for person1 free. So he can be assigned that sweets. If this is not possible, we go to the next
//priority in person1's list.
bool distribute(int person, vector<vector<int>>& dist, vector<vector<int>>& prefs, vector<int>& diff_sweets, int& s_c, int t, int value, int s_cMain)
{
	for (int i = value; i < t; ++i)
	{
		//if (person == 0 and value == (t - 1))
		//	return false;

		if (prefs[person][i])
		{
			if (s_c > diff_sweets[i])
			{
				bool k = true;
				if (person != 0)
					k = move_around(person - 1, dist, prefs, diff_sweets, s_c - diff_sweets[i], t, i, s_cMain);

				//if (k)
				{
					s_c = s_c - diff_sweets[i];
					dist[person][i] += diff_sweets[i];
					diff_sweets[i] = 0;
				}


				if (!k && i == (t - 1))
				{
				//	cout << person << ", false1" << endl;
					return false;
				}

			}
			else
			{
				diff_sweets[i] = diff_sweets[i] - s_c;
				dist[person][i] = s_c;
		//		cout << person << ", true1" << endl;
				return true;
			}
		}

		if (s_c > 0 && i == (t - 1))
		{
			int temp = std::accumulate(dist[person].begin(), dist[person].end(), 0);

			if (temp > s_cMain)
			{
			//	cout << person << ", true2" << endl;
				return true;
			}
			else
			{
		//		cout << person << ", false2" << endl;
				return false;
			}
		}


		if (s_c == 0)
		{
		//	cout << person << ", false3" << endl;
			return true;
		}

		//	int num = 0;
		//	num = std::accumulate(diff_sweets.begin(), diff_sweets.end(), 0);

		//	if (num == smodc)
		//		return true;
	}

	return true;

}


int make_space(int person, int candy, vector<vector<int>>& assigned, vector<int>& dif_sweets, vector<vector<int>>& dist, int s_c, int count, vector<vector<int>>& total_prefs)
{
	int k = s_c;
	int t = dif_sweets.size();
	for (int j = candy + 1; (j < t) && (s_c != 0); ++j)
	{
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

	return (k - s_c);
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
			int new_person = assigned[candy][index - 1];
			int toAssignSub = min(dist[new_person][candy], toAssign);
			ktemp = make_space(new_person, candy, assigned, dif_sweets, dist, toAssignSub, count, total_prefs);
			k = k + ktemp;

			if (dist[new_person][candy] == 0)
			{
				assigned[candy].erase(assigned[candy].begin() + index - 1);
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
	int z = 20;
	while (z != 0)
	{
		vector<int> dif_sweets(t);
		int s = 0;
		for (int i = 0; i < t; ++i)
		{
			int temp;
			//in >> temp;
			temp = random(1, 10);
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
				//in >> temp;
				temp = random(1, t);
				total_prefs[i][j] = temp;
				temp_min = min(temp_min, temp);
			}
			min_row[i] = temp_min;
		}

		for (int i = 0; i < t; ++i)
		{
			cout << dif_sweets[i] << " ";
		}

		cout << endl;

		for (int i = 0; i < c; ++i)
		{
			for (int j = 0; j < t; ++j)
			{
				cout << total_prefs[i][j] << " ";
			}
			cout << endl;
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
			int possible = true;
			int k = 0;

			for (int i = 0; i < c; ++i)
			{
				k = 0;
				for (int j = 0; j < t; ++j)
				{
					if (total_prefs[i][j] <= count)
					{
						int ktemp = try_assign(i, j, assigned, diff_sweets, dist, s_c - k, count, total_prefs);

						if (ktemp > (s_c - k))
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

		//method 2
		int count1 = 1;

		//starting from 1 as count1, i only consider entries with peferences<=count1 for each row and make the other entries 0
		// eg: if the row is 12345 and count1 = 2, then the row becomes 12000
		//this is not rlly required but will be removed when i get a timelimit 
		while (count1 != t)
		{
			vector<int> diff_sweets = dif_sweets;
			vector<vector<int>> prefs(c, vector<int>(t));
			prefs = total_prefs;

			for (auto& v : prefs)
			{
				std::replace_if(v.begin(), v.end(), [count1](const int& x) {return x > count1; }, 0);
			}

			vector<vector<int>> dist(c, vector<int>(t));
			bool possible = true;
			for (int i = 0; i < c; ++i)
			{
				int s_c1 = s_c;
				possible = distribute(i, dist, prefs, diff_sweets, s_c1, t, 0, s_c);

				//cout << "count1: " << count1 << ", " << " child: " << i << "; " << possible << endl;

				if ((std::accumulate(dist[i].begin(), dist[i].end(), 0) == 0))
				{
					possible = false;
				}


				if (!possible)
					break;
			}


			if (possible)
			{
				break;
			}
			else
			{
				++count1;
			}

		}

		cout << count1 << endl;

		if (count != count1)
			cout << "mismatch" << endl;
		--z;
	}
	return 0;
}