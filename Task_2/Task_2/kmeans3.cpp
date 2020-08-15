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

using namespace std;

struct Centers
{
	vector<double> point;
	struct Node *next;

	Centers(std::vector<vector<double>>::size_type sz)
	{
		this->point.reserve(sz);
	}
};


int main()
{
  //	std::ifstream in("p103.t2.in");
	
	int d;
	double R;
	
	//in >> d >> R;
	//R = R * R;

	string line;
	//getline(in, line);
	//istringstream iss(line);
	cin >> d >> R;

	vector<vector<double>> centers;
	centers.reserve(100);
	//std::vector<vector<double>>::size_type sz;
	//sz = centers.capacity();
	

	cin.ignore(256, '\n');
	while (getline(cin, line))
	{
		istringstream iss(line);
		vector<double> numbers(d);
		
		for (int i = 0; i < d; ++i)
		{
			iss>>numbers[i];
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
				diff = sqrt(diff);

  				if (diff <= R)
				{
					mark = 1;
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

	//in.close();

 	return 0;
}