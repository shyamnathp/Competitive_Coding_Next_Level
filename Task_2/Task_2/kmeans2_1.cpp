#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <iomanip>

using namespace std;

//this method finds the closest point to the query (key) in the centers vector
inline double find_center(double key, const vector<double> &centers, int low, int high, int endIndex)
{
	if (low > high)
	{
		/*finally key would fall between two centers, finding the distance to both the centers 
		and return the center to which the distance is minimum
		*/
		double l = abs(centers[low]-key);
		double h = abs(centers[high]-key);
		if (l >= h)
			return centers[high];
		else
			return centers[low];
	}

	auto mid = (high + low) / 2;
		
	if (centers[mid] == key)
		return centers[mid];
	else if (centers[mid] > key)
	{ 
		//this case is needed because mid-1 will be a nullptr if it is not
		if (mid != 0)
			return find_center(key, centers, low, mid - 1, endIndex);
		else
			return centers[mid];
	}
	else
	{ 
		// this case is needed because mid + 1 will be a nullptr if it is not
		if (mid != endIndex)
		{
			return find_center(key, centers, mid+1, high, endIndex);
		}
	    else 
    		return centers[mid];
	}

}

int main()
{
	int c, q;
	double R;

	cin >> c >> q >> R;

	//reading c center into vector centers
	vector<double> centers(c);
	//copy_n(istream_iterator<double>(cin), c, centers.begin());
	for (int i = 0; i < c; ++i)
		cin >> centers[i];
	//sorting them since we are using binary search like mechanism
	std::sort(centers.begin(), centers.end());

	//reading query points into vector queries
	vector<double> queries(q);
	//copy_n(istream_iterator<double>(cin), q, queries.begin());
	for (int i = 0; i < q; ++i)
		cin >> queries[i];

	for (int i = 0; i < q; ++i)
	{ 
		auto query = queries[i];

		double closest = find_center(query, centers, 0, c-1, c-1);

		if (abs(closest - query) <= R)
			cout << fixed << setprecision(2) << closest << endl;
		else
			cout << "none in range" << endl;
	}

	return 0;
}