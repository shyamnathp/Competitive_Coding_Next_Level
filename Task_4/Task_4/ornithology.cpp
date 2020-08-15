#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <cmath>
#include <iostream>
#include <climits>
#include <limits>
#include <queue>
#include <random>

using namespace std;
constexpr static double INF = numeric_limits<double>::max();

template <typename vec>
void print_r_entry(const vec &T) {
	for (int i = 0; i < T.size(); ++i) {
		cout << T[i].x << ", " << T[i].y << ", " << T[i].z << endl;
	}
}

template <typename vec>
void print_oned(const vec &T) {
	for (int i = 0; i < T.size(); ++i) {
		cout << T[i] << ", ";
	}
	cout << endl;
}
template <typename vec>
void print_twod(const vec &T) {
	for (int i = 0; i < T.size(); ++i) {
		for (int j = 0; j < T[i].size(); ++j) {
			cout << T[i][j] << ", ";
		}
		cout << endl;
	}
}

template <typename vec>
void print_goosepath(const vec &T) {
	for (int i = 0; i < T.size(); ++i) {
		for (int j = 0; j < T[i].size(); ++j) {
			cout << T[i][j].x << ", " << T[i][j].y << ", " << T[i][j].z << endl;
		}
		cout << endl;
	}
}

template <typename vec>
void print_twod_pair(const vec &T) {
	for (int i = 0; i < T.size(); ++i) {
		for (int j = 0; j < T[i].size(); ++j) {
			cout << T[i][j].first << ", " << T[i][j].second << endl;
		}
		cout << endl;
	}
}

template <typename vec>
void print_oned_pair(const vec &T) {
	for (int i = 0; i < T.size(); ++i) {
		cout << T[i].first << ", " << T[i].second << endl;
	}
	cout << endl;
}

struct RPoint {
	double x, y, z;
	RPoint() : x{ 0 }, y{ 0 }, z{ 0 }  {}
	RPoint(double x, double y, double z) : x(x), y(y), z(z) {}

	bool operator<(const RPoint &o) const {
		if (x != o.x) {
			return x < o.x;
		}
		if (y != o.y) {
			return y < o.y;
		}
		return z < o.z;
	}
};


struct Point {
	int x, y, z;
	Point(int x, int y, int z) : x(x), y(y), z(z) {}

	bool operator<(const Point &o) const {
		if (x != o.x) {
			return x < o.x;
		}
		if (y != o.y) {
			return y < o.y;
		}
		return z < o.z;
	}
};

double square(double value) {
	return value * value;
}

double squared_l2_distance(RPoint first, RPoint second, int dim) {
	double sum = square(first.x - second.x);

	if (dim >= 2) {
		sum += square(first.y - second.y);
	}

	if (dim >= 3) {
		sum += square(first.z - second.z);
	}
	return sum;
}

vector<RPoint> k_means(const vector<RPoint> &data,
	int k,
	size_t number_of_iterations,
	int dim) {
	int total_points = data.size();
	int points_k = k;
	static random_device seed;
	static mt19937 random_number_generator(seed());
	uniform_int_distribution<size_t> indices(0, data.size() - 1);

	if (k > total_points) {
		points_k = total_points;
	}

	vector<int> used_points;

	vector<RPoint> means(k);

	for (int i = 0; i < points_k; i++) {
		while (true) {
			int index = indices(random_number_generator);
			//int index = rand() % total_points;
			if (find(used_points.begin(), used_points.end(), index) == used_points.end()) {
				used_points.push_back(index);
				means[i] = data[index];
				break;
			}
		}
	}

	for (int i = points_k; i < k; ++i) {
		int index = indices(random_number_generator);
		//int index = rand() % total_points;
		used_points.push_back(index);
		means[i] = data[index];
	}

	vector<size_t> assignments(data.size());
	for (size_t iteration = 0; iteration < number_of_iterations; ++iteration) {
		// Find assignments.
		for (size_t point = 0; point < data.size(); ++point) {
			double best_distance = INF;
			size_t best_cluster = 0;
			for (size_t cluster = 0; cluster < k; ++cluster) {
				const double distance =
					squared_l2_distance(data[point], means[cluster], dim);
				if (distance < best_distance) {
					best_distance = distance;
					best_cluster = cluster;
				}
			}
			assignments[point] = best_cluster;
		}

		// Sum up and count points for each cluster.
		vector<RPoint> new_means(k);
		vector<size_t> counts(k, 0);
		for (size_t point = 0; point < data.size(); ++point) {
			const auto cluster = assignments[point];
			new_means[cluster].x += data[point].x;
			if (dim >= 2) {
				new_means[cluster].y += data[point].y;
			}
			if (dim >= 3) {
				new_means[cluster].z += data[point].z;
			}
			counts[cluster] += 1;
		}

		// Divide sums by counts to get new centroids.
		for (size_t cluster = 0; cluster < k; ++cluster) {
			// Turn 0/0 into 0/1 to avoid zero division.
			const auto count = max<size_t>(1, counts[cluster]);
			means[cluster].x = new_means[cluster].x / count;
			if (dim >= 2) {
				means[cluster].y = new_means[cluster].y / count;
			}
			if (dim >= 3) {
				means[cluster].z = new_means[cluster].z / count;
			}
		}
	}

	return means;
}

double euclidean_distance(RPoint &r_i, Point &p_j) {
	double dist = square(r_i.x - p_j.x)
		+ square(r_i.y - p_j.y)
		+ square(r_i.z - p_j.z);

	return dist;
}

void findAllPathsRec(vector<vector<double>> &dist, int i, int j, int m, int n, vector<double> &path, int pi, vector<double> &max_vec) {
	if (i == m - 1) {
		for (int k = j; k < n; k++) {
			path[pi + k - j] = dist[i][k];
		}
		double max_value = path[0];
		for (int l = 0; l < pi + n - j; l++) {
			//cout << path[l] << " ";
			max_value = max(max_value, path[l]);
		}
		max_vec.push_back(max_value);
		//cout << endl;
		return;
	}

	if (j == n - 1) {
		for (int k = i; k < m; k++) {
			path[pi + k - i] = dist[k][j];
		}
		double max_value = path[0];
		for (int l = 0; l < pi + m - i; l++) {
			//cout << path[l] << " ";
			max_value = max(max_value, path[l]);
		}
		max_vec.push_back(max_value);
		//cout << endl;
		return;
	}

	path[pi] = dist[i][j];

	findAllPathsRec(dist, i + 1, j, m, n, path, pi + 1, max_vec);

	findAllPathsRec(dist, i, j + 1, m, n, path, pi + 1, max_vec);

	findAllPathsRec(dist, i + 1, j + 1, m, n, path, pi + 1, max_vec);

}

void findAllPaths(vector<vector<double>> &dist, int m, int n, vector<double> &max_vec) {
	vector<double> path(m + n);

	findAllPathsRec(dist, 0, 0, m, n, path, 0, max_vec);
}

double find_min_max(vector<RPoint> &r, vector<Point> &p, int m, int n) {

	double min_val = 0;
	double curr_min = INF;

	vector<vector<double>> distances(m, vector<double>(n));
	for (int temp_j = 0; temp_j < m; ++temp_j) {
		for (int temp_i = 0; temp_i < n; ++temp_i) {
			distances[temp_j][temp_i] = euclidean_distance(r[temp_i], p[temp_j]);
		}
	}

	vector<double> max_vec;
	//print_twod(distances);
	findAllPaths(distances, m, n, max_vec);

	//print_oned(max_vec);
	for (int i = 0; i < max_vec.size(); ++i) {
		curr_min = min(curr_min, max_vec[i]);
	}

	return curr_min;
}



int main() {

	int s;
	cin >> s;

	int n;
	cin >> n;

	vector<vector<Point>> goose_path(s);
	vector<RPoint> all_points;
	int pointId = 1;

	for (int i = 0; i < s; ++i) {
		int m;
		cin >> m;
		for (int j = 0; j < m; ++j) {
			int x;
			int y;
			int z;
			cin >> x;
			cin >> y;
			cin >> z;
			goose_path[i].push_back(Point(x, y, z));
			pointId++;
			all_points.push_back({ double(x), double(y), double(z) });
		}
	}

	int iters = 100;

	//print_O(r);

	vector <RPoint> r = k_means(all_points, n, iters, 3);
	sort(r.begin(), r.end());
	print_r_entry(r);
	cout << endl;
	double max_value = 0;

	for (int i = 0; i < 1; ++i) {
		sort(goose_path[i].begin(), goose_path[i].end());
		//print_r_entry(goose_path[i]);
		//cout << endl;
		double min = find_min_max(r, goose_path[i], goose_path[i].size(), n);
		max_value = max(max_value, min);
	}

	cout << setprecision(3) << max_value << endl;

	return 0;
}
