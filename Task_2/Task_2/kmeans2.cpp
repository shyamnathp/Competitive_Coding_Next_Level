#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <iomanip>

using namespace std;


void print_center(vector<double>::iterator low, double query, double R)
{
	if (abs((*low) - query) <= R)
		cout << fixed << setprecision(2) << *low << "\n";
	else
		cout << "none in range" << "\n"; 
}

void find_center(double query, vector<double> centers,int c,double R)
{
	auto low = lower_bound(centers.begin(), centers.end(), query);
//	int index = std::distance(centers.begin(),low);
//	cout << fixed << setprecision(2) << low - centers.begin() << "\n";
	auto l = low - centers.begin();
	if (l == 0)
	{
		print_center(low, query, R);
	}
    else if (l > (c-1))
	{
		auto check = std::prev(low,1);
		//return check;
		print_center(check, query, R);
	}
	else
	{
		double min1, min2;
		min1 = abs((*low) - query);
		min2 = abs((*(low - 1)) - query);

		if (min1 < min2)
		{
			print_center(low, query, R);
		}
		else
		{
			print_center(std::prev(low, 1), query, R);
		}
     
	} 
}

int main()
{
	int c, q;
	double R;

	cin >> c >> q >> R;

	vector<double> centers(c);
	cin.clear();
	copy_n(istream_iterator<double>(cin),c,centers.begin());

	std::sort(centers.begin(), centers.end());

	vector<double> queries(q);
	cin.clear();
	copy_n(istream_iterator<double>(cin), q, queries.begin());

	for (int i = 0; i < q; ++i)
	{
	    find_center(queries[i], centers, c, R);
	//	print_center(it,queries[i],R);

	}

	return 0;
}