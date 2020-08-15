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


bool isPossible(vector<int>& arr, int n, int C, int mid, vector<int>& places)
{
	// Variable magnet will store count of magnets 
	// that got placed and currPosition will store 
	// the position of last placed magnet 
	int magnet = 1, currPosition = arr[0];
	int j = 0;
	places[0] = arr[0];

	for (int i = 1; i < n; i++) {

		// If difference between current index and 
		// last placed index is greater than or equal to mid 
		// it will allow placing magnet to this index 
		if (arr[i] - currPosition >= mid) {

			places[magnet] = arr[i];

			magnet++;

			// Now this index will become 
			// last placed index 
			currPosition = arr[i];

			// If count of magnets placed becomes C 
			if (magnet == C)
				return true;
		}
	}

	// If count of placed magnet is 
	// less than C then return false 
	return false;
}

// Function for modified binary search 
int binarySearch(int n, int C, vector<int>& arr, vector<int>& places)
{
	int lo, hi, mid, ans;

	// Sort the indices in ascending order 
	sort(arr.begin(), arr.end());

	// Minimum possible distance 
	lo = 0;

	// Maximum possible distance 
	hi = arr[n - 1];

	ans = 0;

	// Run the loop until lo becomes 
	// greater than hi 
	while (lo <= hi) {

		mid = (lo + hi) / 2;

		// If not possibble, decrease value of hi 
		if (!isPossible(arr, n, C, mid, places))
			hi = mid - 1;
		else {
			ans = max(ans, mid);
			lo = mid + 1;
		}
	}

	// Return maximum possible distance 
	return ans;
}

// Driver code 
int main()
{
	std::ifstream in("p103.t2.in");
	int i1, n;
	in >> i1 >> n;


	vector<int> arr(n);
	//map<int, int>::iterator i = valueN.begin();

	for (int i = 0; i < n; ++i)
	{
		int val;
		in >> val;
		arr[i] = val;
	}

	vector<int> places(i1);
	cout << binarySearch(n, i1, arr, places) << endl;

	return 0;
}