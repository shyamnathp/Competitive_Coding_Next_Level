#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <iomanip>

using namespace std;

//this function makes the compariosn between distance and R
void print_center(double closest, double query, double R)
{
	if (abs(closest - query) <= R)
		cout << fixed << setprecision(2) << closest << endl;
	else
		cout << "none in range" << endl;
}

double findClosest(vector<double> centers, double query)
{
	double dif = fabs(centers[0] - query);
	double close = centers[0];
	for(auto &c: centers)
	{
		double tdif = fabs(c - query);
		if (tdif < dif)
		{
		    dif = tdif;
			close = c;
		}
		else if (tdif == dif)
		{
			close = c > close ? close : c;
		}
	}
	return close;
}

int main()
{
	int c, q;
	double R;

	cin >> c >> q >> R;

	//reading c center into vector centers
	vector<double> centers(c);
	cin.clear();
	copy_n(istream_iterator<double>(cin), c, centers.begin());

	//reading query points into vector queries
	vector<double> queries(q);
	cin.clear();
	copy_n(istream_iterator<double>(cin), q, queries.begin());

	for (int i = 0; i < q; ++i)
	{
		//double closest = find_center(queries[i], centers, 0, c - 1, c - 1);
		double closest = findClosest(centers, queries[i]);
		print_center(closest, queries[i], R);
	}

	return 0;
}