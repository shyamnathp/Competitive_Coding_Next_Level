#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<double> combination;
double max_val;


template<typename T>
{

}

void pretty_print(const vector<double>& v) {
	static int count = 0;
	cout << "combination no " << (++count) << ": [ ";
	for (int i = 0; i < v.size(); ++i) { cout << v[i] << " "; }
	cout << "] " << endl;
}

void calculate(const vector<double>& v) {
	cout << "nope";
}

void go(vector<double>& probs, int offset, int k) {
	if (k == 0) {
		pretty_print(combination);
		return;
	}
	for (int i = offset; i <= probs.size() - k; ++i) {
		combination.push_back(probs[i]);
		go(probs, i + 1, k - 1);
		combination.pop_back();
	}
}

template <typename vec>
void print_T(const vec &T, const uint64_t n, const uint64_t k) {
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j <= i + 1; ++j) {
			for (int l = 0; l < n; ++l) {
				std::cout << T[i][l][j] << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

int main() {
	vector<double> probs_yes;

	int n;
	cin >> n;

	int k;
	cin >> k;

	probs_yes.reserve(n);

	for (int i = 0; i < n; ++i) {
		double x;
		cin >> x;
		probs_yes.push_back(x);
	}

	std::sort(probs_yes.begin(),probs_yes.end());

	vector<double> yes(k);

	yes = vector<double>

	auto &p = probs_yes;


	std::vector<std::vector<std::vector<double>>> T(
		k, std::vector<std::vector<double>>(
			n, std::vector<double>(k + 1)));

	auto &first_row = T[0];
	T[0][0][1] = p[0];
	T[0][0][0] = 1 - p[0];
	for (int j = 1; j < n; ++j) {
		first_row[j][1] = std::max(first_row[j - 1][1], p[j]);
		first_row[j][0] = std::max(first_row[j - 1][0], p[j]);
	}

	for (int l = 1; l < k; ++l) {
		T[l][l][0] = T[l - 1][l - 1][0] * (1 - p[l]);
		for (int i = 1; i < l + 1; ++i) {
			T[l][l][i] = T[l - 1][l - 1][i] * (1 - p[l]) +
				T[l - 1][l - 1][i - 1] * p[l];
		}
		T[l][l][l + 1] = T[l - 1][l - 1][l] * p[l];
	}

	for (int m = 1; m < k; ++m) {
		for (int i = m + 1; i < n; ++i) {
			T[m][i][0] = T[m - 1][i - 1][0] * (1 - p[i]);
			for (int j = 1; j < m + 2; ++j) {
				T[m][i][j] = std::max(T[m - 1][i - 1][j] * (1 - p[i]),
					T[m - 1][i - 1][j - 1] * p[i]);
			}
		}
	}

	print_T(T, n, k);



	cout << fixed << setprecision(3) << n << endl;

	return 0;
}
