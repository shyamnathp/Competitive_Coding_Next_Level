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

using namespace std;

bool distribute(int person, vector <vector<int>> &dist, vector <vector<int>> &prefs, vector<int> &diff_sweets, int &s_c,
	int t, int value, int s_cMain);


template <typename vec>
void print_vec(const vec &T) {
	for (auto &t : T) {
		cout << t << " ";
	}
	cout << endl;
}

template <typename vec>
void print_2d_vec(const vec &T) {
	for (auto &t : T) {
		for (auto &a : t) {
			cout << a << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//move_around is used go back to the previous person who was assigned a sweet, and tries to assign him someother sweet
bool move_around(int person, vector <vector<int>> &dist, vector <vector<int>> &prefs, vector<int> &diff_sweets, int s_c,
	int t, int value, int s_cMain) {
	if (dist[person][value] > 0) {
		int z1 = min(dist[person][value], s_c);
		int z = z1;
		bool k = distribute(person, dist, prefs, diff_sweets, z, t, value + 1, s_cMain);

		if (z == 0) {
			z = z1;
		}

		if (!k) {
			//print_vec(dist[person]);
			//cout << "movearound, person " << person << ", false1" << endl;
			return false;
		}
		else {
			//cout << "movearound, person " << person << ", setting vars" << endl;
			dist[person][value] = dist[person][value] - z;
			diff_sweets[value] = diff_sweets[value] + z;
		}
	}
	else {
		if (person != 0) {
			//cout << "movearound, person " << person << ", recursion" << endl;
			move_around(person - 1, dist, prefs, diff_sweets, s_c, t, value, s_cMain);
		}
		else {
			//print_vec(dist[person]);
			//cout << "movearound, person " << person << ", false2" << endl;
			return false;
		}
	}

}


//trying to distribute the sweets to the person(person1) under consideration. We start from his top priority, if there are no sweets of
//his top priority, we move back to the previous person(person2) who uses that sweet and try to assign that person(person2) to another sweet thus
//making the sweet for person1 free. So he can be assigned that sweets. If this is not possible, we go to the next
//priority in person1's list.
bool distribute(int person, vector <vector<int>> &dist, vector <vector<int>> &prefs, vector<int> &diff_sweets, int &s_c,
	int t, int value, int s_cMain) {

	for (int i = value; i < t; ++i) {
		//if (person == 0 and value == (t - 1))
		//	return false;

		if (prefs[person][i]) {
			if (s_c > diff_sweets[i]) {
				bool k = true;
				if (person != 0) {
					k = move_around(person - 1, dist, prefs, diff_sweets, s_c - diff_sweets[i], t, i, s_cMain);
				}
				//if (k)
				s_c = s_c - diff_sweets[i];
				dist[person][i] += diff_sweets[i];
				diff_sweets[i] = 0;

				if (!k && i == (t - 1)) {
					//cout << "distribute, person " << person << ", false1" << endl;
					return false;
				}

			}
			else {
				diff_sweets[i] = diff_sweets[i] - s_c;
				dist[person][i] = s_c;
				//cout << "distribute, person " << person << ", true1" << endl;
				return true;
			}
		}

		if (s_c > 0 && i == (t - 1)) {
			int temp = std::accumulate(dist[person].begin(), dist[person].end(), 0);

			if (temp > s_cMain) {
				//cout << "distribute, person "  << person << ", true2" << endl;
				return true;
			}
			else {
				//cout << "distribute, person "  << person << ", false2" << endl;
				return false;
			}
		}


		if (s_c == 0) {
			//cout << "distribute, person "  << person << ", false3" << endl;
			return true;
		}

		//	int num = 0;
		//	num = std::accumulate(diff_sweets.begin(), diff_sweets.end(), 0);

		//	if (num == smodc)
		//		return true;
	}

	return true;

}

int main() {
	//std::ifstream in("p103.t2.in");

	int c, t;
	cin >> c;
	cin >> t;

	vector<int> dif_sweets(t);
	int s = 0;
	for (int i = 0; i < t; ++i) {
		int temp;
		cin >> temp;
		dif_sweets[i] = temp;
		s = s + temp;
	}

	//all the preferences as a matrix
	vector <vector<int>> total_prefs(c, vector<int>(t));

	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < t; ++j) {
			int temp;
			cin >> temp;
			total_prefs[i][j] = temp;
		}
	}

	//print_2d_vec(total_prefs);

	//the candies to be divided to each and smodc is the candies left out
	int s_c = floor(s / c);

	//int smodc = s % c;
	int count = 1;

	//starting from 1 as count, i only consider entries with peferences<=count for each row and make the other entries 0
	// eg: if the row is 12345 and count = 2, then the row becomes 12000
	//this is not rlly required but will be removed when i get a timelimit
	while (count != t) {
		vector<int> diff_sweets = dif_sweets;
		vector <vector<int>> prefs(c, vector<int>(t));
		prefs = total_prefs;

		for (auto &v : prefs) {
			std::replace_if(v.begin(), v.end(), [count](const int &x) { return x > count; }, 0);
		}

		vector <vector<int>> dist(c, vector<int>(t));
		bool possible = true;
		for (int i = 0; i < c; ++i) {
			int s_c1 = s_c;
			possible = distribute(i, dist, prefs, diff_sweets, s_c1, t, 0, s_c);

			//print_2d_vec(dist);
			//cout << "count: " << count << ", " << " child: " << i << "; " << possible << endl;

			if (std::all_of(dist[i].begin(), dist[i].end(), [](int i) { return i == 0; })) {
				//cout << "here_also" << endl;

				possible = false;
			}


			if (!possible)
				break;
		}


		if (possible) {
			break;
		}
		else {
			//cout << "here" << endl;
			++count;
		}

	}

	cout << count << endl;
}
