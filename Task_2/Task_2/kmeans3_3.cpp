#include<iostream>
#include<utility>
#include<vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <chrono>
#include <list>
#include <set>

using namespace std;
 
struct ClosestCmp
{
	bool operator()(const vector<double> &c, const vector<double> &number)
	{
		return c[0] >= number[0];
	}
};

int main()
{
	//auto start = high_resolution_clock::now();
	std::ifstream in("p103.t2.in");

	int d;
	double R;

	//in >> d >> R;
	//R = R * R;

	string line;
	//getline(in, line);
	//istringstream iss(line);
	in >> d >> R;
	R = R * R;

	set<vector<double>,ClosestCmp> centers;
	//centers.reserve(100);
	//std::vector<vector<double>>::size_type sz;
	//sz = centers.capacity();


	in.ignore(256, '\n');
	while (getline(in, line))
	{
		istringstream iss(line);
		vector<double> numbers(d);

		for (int i = 0; i < d; ++i)
		{
			iss >> numbers[i];
		}

		if (!centers.empty())
		{
			set<vector<double>>::iterator pos = std::lower_bound(centers.begin(), centers.end(), numbers, ClosestCmp());
		//	list<vector<double>>::iterator pos = centers.end();

			if (centers.begin() == (prev(centers.end())))
				pos = centers.begin();

			for (int j = 0; j < 2; ++j)
			{

				double diff = 0;

				//this maybe a problem here cos of the copy constructor
				vector<double> close = *pos;
				for (int i = 0; i < d; ++i)
				{
					diff += pow(close[i] - numbers[i], 2);
				}

				if (diff > R)
				{
					centers.insert(numbers);
				}

				if (pos == centers.begin() || pos == prev(centers.end()))
					break;
                
				--pos;
			}
		}
		else
		{
			centers.insert(std::move(numbers));
		}
		//	sz = centers.capacity();
	}

	cout << centers.size() << endl;

	in.close();
	//	auto stop = high_resolution_clock::now();

	//	cout << "time is" << duration_cast<microseconds>(stop - start).count();
	return 0;
}