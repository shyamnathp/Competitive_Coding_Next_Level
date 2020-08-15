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
	std::unique_ptr<Centers> next;

	Centers(int val)
	{
		this->point.reserve(val);
		this->next = nullptr;
	}

};


int main()
{
	std::ifstream in("p103.t2.in");

	int d;
	double R;

	//in >> d >> R;


	string line;
	//getline(in, line);
	//istringstream iss(line);
	in >> d >> R;
	R = R * R;
	//vector<vector<double>> centers;
	//centers.reserve(100);
	//std::vector<vector<double>>::size_type sz;
	//sz = centers.capacity();

	std::unique_ptr<Centers>  pos, start, r;
	pos = nullptr;
	start = nullptr;
	int count1 = 0, count2 = 0;


	in.ignore(256, '\n');
	while (getline(in, line))
	{
		istringstream iss(line);
		vector<double> numbers(d);

		for (int i = 0; i < d; ++i)
		{
			iss >> numbers[i];
		}

		if (start != nullptr)
		{
			int mark = 0;
			for (auto c = std::move(start); c != nullptr; c= std::move(c->next) )
			{
				double diff = 0;
				for (int i = 0; i < d; ++i)
				{
					diff += pow(c->point[i] - numbers[i], 2);
				}
				//diff = sqrt(diff);

				if (diff <= R)
				{
					mark = 1;
					++count2;
					break;
				}

			}
			if (mark != 1)
			{
				// Create new node dynamically 
				r = std::make_unique<Centers>(d);
				r->point = numbers;
				r->next = nullptr;
				pos->next = std::move(r);
			} 
		}
		else
		{
			// Create new node dynamically 
			pos = std::make_unique<Centers>(d);
			pos->point = numbers;
			start= std::move(pos);
		
		}
		//	sz = centers.capacity();
		++count1;
	}

	cout << count1 - count2 << endl;

	in.close();

	return 0;
}