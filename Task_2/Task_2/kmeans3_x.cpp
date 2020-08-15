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
#include <set>

using namespace std;
using namespace std::chrono;

double distanceFunc(const vector<double> &point, const vector<double> &point1)
{
	double diff = 0;
	for (int i = 0; i < point.size(); ++i)
	{
		diff += pow(point[i] - point1[i], 2);
	}

	return sqrt(diff);
}

struct Point
{
	vector<double> point;
	double distance;

	Point(const vector<double> &point)
	{
		this->point = std::move(point);
		double dist = 0;
		for (int i = 0; i < point.size(); ++i)
		{
			dist += pow(point[i], 2);
		}
		this->distance = sqrt(dist);
	}

};

struct SortDist
{
	bool operator()(const Point &c, const Point &number) const
	{
		return c.distance < number.distance;
	}
};

int main()
{
	//	auto start = high_resolution_clock::now();
	//std::ifstream in("p103.t2.in");

	int d;
	double R;

	string line;

	cin >> d >> R;
	//R = R * R;

	multiset<Point, SortDist> centers;

	cin.ignore(256, '\n');
	while (getline(cin, line))
	{
		istringstream iss(line);
		vector<double> numbers(d);

		for (int i = 0; i < d; ++i)
		{
			iss >> numbers[i];
		}

		Point numb(numbers);

		if (!centers.empty())
		{
			auto pos = centers.lower_bound(numb);
			//auto pos = std::lower_bound(centers.begin(), centers.end(), numb, SortDist());
			auto pos1 = pos;
			if (pos == centers.end())
			{
				pos = prev(centers.end());
				int mark = 0;
			   while(((*pos).distance) >= (numb.distance - R))
			   {
				double dist = distanceFunc((*pos).point,numb.point);
				if (dist <= R)
				{
					mark = 1;
				   break;
				}
				
				if (pos != centers.begin())
					advance(pos, -1);
				else
					break;
			   }

			   if (mark == 0)
			   {
				   centers.insert(pos1,numb);
				 //  centers.sort(SortDist());
			   }
			}
			else if(pos == centers.begin())
			{
				int mark = 0;
				while ((*pos).distance <= (numb.distance + R))
				{
					double dist = distanceFunc((*pos).point, numb.point);
					if (dist <= R)
					{
						mark = 1;
						break;
					}

					if (next(pos, 1) != centers.end())
						advance(pos, 1);
					else
						break;
				}

				if (mark == 0)
				{
					centers.insert(pos1,numb);
				//	centers.sort(SortDist());
				}
			}
			else
			{
				auto posPrev = prev(pos);
				
				int mark1 = 0;
				while (((*posPrev).distance) >= (numb.distance - R))
				{
					double dist = distanceFunc((*posPrev).point, numb.point);
					if (dist <= R)
					{
						mark1 = 1;
						break;
					}

					if (posPrev != centers.begin())
						advance(posPrev, -1);
					else
						break;
				}

				if (mark1 != 1)
				{
					int mark = 0;
					while ((*pos).distance <= (numb.distance + R))
					{
						double dist = distanceFunc((*pos).point, numb.point);
						if (dist <= R)
						{
							mark = 1;
							break;
						}

						if (next(pos, 1) != centers.end())
							advance(pos, 1);
						else
							break;
					}

					if (mark == 0)
					{
						centers.insert(pos1,numb);
						//centers.sort(SortDist());
					}
				}
			}

			
			
		}
		else
		{
			centers.insert(numb);
		}
		
	}

	cout << centers.size() << endl;

  /* 	cout << endl << "the centers after addition"<<endl;
	for (auto &c : centers)
	{
		//auto pos = std::lower_bound(centers.begin(), centers.end(), numb, SortDist());
		//Point k = *pos;
		cout << c.point[0] << " " << c.point[1] << " " << c.distance << " " << endl;
		//cout << k.point[0] << " " << k.point[1] <<" "<< k.distance << endl;;
		cout << endl;
	} */
	//in.close();
	//auto stop = high_resolution_clock::now();

	//cout << "time is" << duration_cast<microseconds>(stop - start).count();
	return 0;
}