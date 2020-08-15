#include <iostream>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <iterator>
#include <map>

using namespace std;

constexpr static int INF = numeric_limits<int>::max();

void combinationUtil(vector<int>& arr, vector<int>& data, vector<int>& finVec,
	int start, int end,
	int index, int r);

void printCombination(vector<int>& arr, vector<int>& data, vector<int>& finVec, int n, int r)
{
	combinationUtil(arr, data, finVec, 0, n - 1, 0, r);
}

void combinationUtil(vector<int>& arr, vector<int>& data,vector<int>& finVec, int start, int end, int index, int r)
{

	if (index == r)
	{

		int myNumber = 0;
		int final1 = 0;

		for (int j = 0; j < arr.size(); ++j)
		{
			myNumber = arr[j];

			int distance = abs(data[0] - myNumber);
			int idx = 0;
			for (int c = 1; c < r; c++) {
				int cdistance = abs(data[c] - myNumber);
				if (cdistance < distance) {
					idx = c;
					distance = cdistance;
				}
			}
			int theNumber = data[idx];

			final1 = final1 + abs(theNumber - myNumber);
		}

		//for (int j = 0; j < r; j++)
	    //cout << data[j] << " ";

		int final2 = 25 * arr.size() - final1;
		//cout << "final1 is" << final2 << endl;
		finVec.push_back(final2);
		return;
	}
 
	for (int i = start; i <= end &&
		end - i + 1 >= r - index; i++)
	{
		data[index] = arr[i];
		combinationUtil(arr, data, finVec, i + 1, end, index + 1, r);
	}
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


int findMedian(set<int>& a, int n)
{
	std::set<int>::iterator it2 = a.begin();

	// check for even case 
	if (n % 2 != 0)
	{
		std::advance(it2, (a.size()) / 2);
		return (*it2);
	}

	std::advance(it2, a.size() / 2);
	int i1 = *it2;
	int i2 = *(prev(it2));
	return (i1 + i2) / 2.0;
}

std::vector<int> slice(std::vector<int> const &v, int m, int n)
{
	auto first = v.cbegin() + m;
	auto last = v.cbegin() + n + 1;

	std::vector<int> vec(first, last);
	return vec;
}

int minSum(vector<int> &a, int begin, int end) {
	// Median of the array

	//cout << "begin " << begin << endl;
	//cout << "end " << end << endl;
	//print_vec(a);

	if (end == begin) {
		return 0;
	}

	//vector<int> arr;

	//std::vector<int> arr(&a[begin], &a[end]+1);

	//print_vec(arr);

	int x = a[(end - begin) / 2 + begin];

	int sum = 0;

	// Calculate the minimized sum
	for (int i = begin; i < end + 1; ++i) {
		sum += abs(a[i] - x);
	}
	// Return the required sum
	return sum;
}

vector<int> returnAllDistances(vector<int> &a) {
	// Median of the array

	vector<int> distances(a.size());
	int j = 0;
	for (int i = 0; i < a.size(); ++i) {
		distances[i] = a[i] - a[j];
		j = i;
	}
	//print_vec(distances);
	return distances;
}

int sumOfMinAbsDifferences(vector<int> &nums, vector<int> &all_dists, int begin, int end) {


	if (end == begin) {
		//cout << 0 << endl;
		return 0;
	}
	//cout << "begin " << begin << endl;
	//cout << "end " << end << endl;

	//print_vec(a);

	int sum = 0;

	sum += abs(nums[begin] - nums[begin + 1]);

	if (begin + 1 != end) {
		sum += abs(nums[end] - nums[end - 1]);
	}

	for (int i = begin + 1; i < end - 1; i++) {
		//cout << nums[i] << " ";
		sum += min(abs(nums[i] - nums[i - 1]), abs(nums[i] - nums[i + 1]));
	}
	//cout << endl;

	//cout << "sum " << sum << endl;
	//print_vec(nums);
	return sum;
}

int minCost(vector<int> &a, int n, int k) {
	// Create a dp[][] table and initialize 
	// all values as infinite. dp[i][j] is 
	// going to store optimal partition cost 
	// for arr[0..i-1] and j partitions 
	vector<vector<int>> dp(n + 1, (vector<int>(k + 1, INF)));

	// Fill dp[][] in bottom up manner 
	dp[0][0] = 0;

	// Current ending position (After i-th
	// iteration result for a[0..i-1] is computed.
	for (int i = 1; i < n + 1; ++i) {
		// j is number of partitions
		for (int j = 1; j < k + 1; ++j) {

			// Picking previous partition for 
			// current i. 
			for (int m = i - 1; m >= 0; --m) {
				dp[i][j] = (int)min((long)dp[i][j], ((long)dp[m][j - 1] + minSum(a, m, i - 1)));
			}
		}

	}

	//print_2d_vec(dp);
	return dp[n][k];
}

int Duckburg(vector<int>& arr, int n, int r)
{
	std::sort(arr.begin(), arr.end());
	cout << 25 * n - minCost(arr, n, r) << endl;
	return (25 * n - minCost(arr, n, r));
}

// Driver code  
int main()
{
	int n;
	cin >> n;

	int r;
	cin >> r;

    for (int z = 0; z < 100; ++z)
	{
		vector<int> arr(n);

		for (int i = 0; i < n; ++i)
		{
			arr[i] = random(1, 1000);
		}

		//arr = {255, 278, 373, 304, 99};

		for (int i = 0; i < n; ++i)
		{
			cout << arr[i] << " ";
		}
		//int arr[] = { 1, 2, 3, 4, 5 };
		//int n = sizeof(arr) / sizeof(arr[0]);

		vector<int> data(r);
		vector<int> finVec;
		printCombination(arr, data, finVec, n, r);

		auto it = max_element(std::begin(finVec), std::end(finVec));
		cout <<"final " << *it <<" ";


		int duck = Duckburg(arr, n, r);

		if (duck != *it)
			cout << "mismatch";

		cout << endl;
	}
}
