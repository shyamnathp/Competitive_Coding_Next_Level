#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
#include <iterator>
#include <cmath>
#include <vector>
#include <set>
#include <numeric>

using namespace std;

std::vector<int> slice(std::vector<int> const &v, int m, int n)
{
	auto first = v.cbegin() + m;
	auto last = v.cbegin() + n + 1;

	std::vector<int> vec(first, last);
	return vec;
}

int minSum(vector<int>& arr, int n)
{
	// Median of the array 
	int x = arr[n / 2];

	int sum = 0;

	// Calculate the minimized sum 
	for (int i = 0; i < n; i++)
		sum += abs(arr[i] - x);

	// Return the required sum 
	return sum;
}

void partition(vector<int>& n_values, int index, int i1, int final, set<int>& final_set)
{
	if (i1 == 1)
	{
		int sum = 0;
		for (int i = index; i < n_values.size(); ++i)
		{
			std::vector<int> sub_vec = slice(n_values, index, i+1);
			sum =  minSum(sub_vec, sub_vec.size());
		//    final = min(final, partition(n_values, i + 1, i1, 10000));
		}

		final_set.insert(final + sum);

		return ;
	}


	//int final = 0;

	i1 = i1 - 1;
	for (int i = index; i < n_values.size(); ++i)
	{
		int sum = 0;
		std::vector<int> sub_vec = slice(n_values, i, index);
		sum =  minSum(sub_vec, sub_vec.size());
		partition(n_values, i + 1, i1, sum, final_set);
	}

	return ;
}

int main()
{
	std::ifstream in("p103.t2.in");

	int i1, n;
	in >> i1 >> n;

	vector<int> n_values(n);

	vector<int> i_values(i1);



	return 0;
}