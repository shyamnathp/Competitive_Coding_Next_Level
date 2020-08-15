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
#include <iomanip>

using namespace std;

std::vector<int> slice(std::vector<int> const &v, int m, int n)
{
	auto first = v.cbegin() + m;
	auto last = v.cbegin() + n + 1;

	std::vector<int> vec(first, last);
	return vec;
}


//this function finds the median and the absolute difference to the other elements in the slice
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

int partition(vector<int>& n_values, int index, int i1, int sum, set<int>& final_set)
{
	if (i1 == 1)
	{
		//int sum = 0;
		//for (int i = index; i < n_values.size(); ++i)
		{
			std::vector<int> sub_vec = slice(n_values, index, n_values.size()-1);
			sum = sum + minSum(sub_vec, sub_vec.size());
			//    final = min(final, partition(n_values, i + 1, i1, 10000));
		}

		//final_set.insert(final + sum);

		return sum;
	}


	//int final = 0;


	//we only need i1-1 interals for selecting i1 values
	//whenever index is 0, the sum starts from 0
	// so the idea here is to slice the vector into i1-1 parts recursively
	//taking a small example 4,6,8 and i = 2
	// this will be 2-1 pars
	// 4 | 6,8 => slice 1 has sum=0 and is passed to 6,8 which gives sum = sum(0) + minsum(2) = 2
   	// 4, 6 | 8 => gives 2 again
	// i take the minimu of these returned values

	i1 = i1 - 1;
	int final1 = std::numeric_limits<int>::max();
	for (int i = index; i < (n_values.size()-i1); ++i)
	{
		int sum1 = 0;
		if (index == 0)
		{
			sum = 0;
		}

		std::vector<int> sub_vec = slice(n_values, index, i);
		sum1 = sum1 + minSum(sub_vec, sub_vec.size());
		final1 = min(final1, partition(n_values, i + 1, i1, sum + sum1 , final_set));
	}

	return final1;
}

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


int main()
{
	//std::ifstream in("p103.t2.in");

	int i1, n;
	cin >> i1 >> n;

	vector<int> n_values(n);
	for (int i = 0; i < n; ++i)
	{
		int val;
		cin >> val;
		n_values[i] = val;
	}

	//n random value generator here, u can maybe uncomment the above to input the n values

	/*for (int i = 0; i < n; ++i)
	{
		n_values[i] = random(1, 1000);
	}*/


	//sort the values inititally
	std::sort(n_values.begin(), n_values.end());


	//these two variables are not used and can be removed
	vector<int> i_values(i1);
	set<int> final_set;

	//n_values = {99, 255, 278, 304, 373};
	int final = partition(n_values, 0, i1, 0, final_set);

	cout << 25*n - final;
	return 0;
}