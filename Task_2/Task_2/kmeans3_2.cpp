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

using namespace std;
using namespace std::chrono;

int main()
{
	auto start = high_resolution_clock::now();
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

	list<vector<double>> centers;
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
			int mark = 0;
			for (auto &c : centers)
			{
				double diff = 0;
				for (int i = 0; i < d; ++i)
				{
					diff += pow(c[i] - numbers[i], 2);
				}
				//diff = sqrt(diff);

				if (diff <= R)
				{
					mark = 1;
					//cout << c[0] <<" "<<c[1]<< endl;
					break;
				}

			}
			if (mark != 1)
				centers.push_back(numbers);
		}
		else
		{
			centers.push_back(numbers);
		}
		//	sz = centers.capacity();
	}

	cout << centers.size() << endl;

	for (auto &c : centers)
	{
		cout << c[0] <<" "<< c[1]<<endl;
	}

	in.close();
	auto stop = high_resolution_clock::now();

	cout << "time is" << duration_cast<microseconds>(stop - start).count();
	return 0;
}