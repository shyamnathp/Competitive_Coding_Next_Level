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

/*struct ClosestCmp
{
	bool operator()(const vector<double> &c, const vector<double> &number)
	{
	   for(int i=0;i<c.size();++i)
		return c[i] < number[i];
	}
};*/

typedef set<vector<double>> SetVec;

inline bool find_center(const vector<double> &key, const SetVec &centers, int low, int high, int k, double R)
{
	if (low > high)
	{
		/*finally key would fall between two centers, finding the distance to both the centers
		and return the center to which the distance is minimum
		*/
		auto it = centers.begin();
		advance(it, high);
		vector<double> cHigh = *it;
		advance(it,1);
		vector<double> cLow = *it;
		double l = 0, h = 0;
		for (int i = 0; i < cHigh.size(); ++i)
		{
			l += pow(cLow[i] - key[i], 2);
			h += pow(cHigh[i] - key[i], 2);
		}
		if (l <= R || h <= R)
		{

			return true;
		}
		else
			return false;
	}

	auto mid = (high + low) / 2;

	auto it = centers.begin();
	std::advance(it, mid);
	vector<double> MidVec = *it;

	for (int i = 0; i < MidVec.size(); ++i)
	{
		if (MidVec[i] == key[i])
		{
			if(i == (MidVec.size()-1))
				return true;
			
			continue;
		}
		else if (MidVec[i] > key[i])
		{
			//this case is needed because mid-1 will be a nullptr if it is not
			if (mid != 0)
				return find_center(key, centers, low, mid - 1, i, R);
			else
			{
				double diff = 0;
				for (int i = 0; i < key.size(); ++i)
				{
					diff += pow(MidVec[i] - key[i], 2);
				}
				if (diff > R)
					return false;
				else
				{
			//		cout << MidVec[0] << " " << MidVec[1]<<endl;
					return true;
				}
			}
		}
		else
		{
			// this case is needed because mid + 1 will be a nullptr if it is not
			if (mid != (centers.size()-1))
			{
				return find_center(key, centers, mid + 1, high, i, R);
			}
			else
			{
				double diff = 0;
				for (int i = 0; i < key.size(); ++i)
				{
					diff += pow(MidVec[i] - key[i], 2);
				}
				if (diff > R)
					return false;
				else
				{
					cout << MidVec[0] << " " << MidVec[1]<<endl;
					return true;
				}
			}
				
		}
	}
}

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

	SetVec centers;
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
			bool closest = find_center(numbers, centers, 0, centers.size() - 1, 0, R);
			//auto closes = std::lower_bound(centers.begin(),centers.end(),numbers);
			//auto temp = centers.begin();
			//vector<double> temp0 = *temp;
			//auto closest = *closes;
			
			if (closest == false)
			{
				centers.insert(numbers);
			}
		}
		else
		{
			centers.insert(numbers);
		}
		//	sz = centers.capacity();
	}

	cout << centers.size() << endl;

	for (auto &c : centers)
	{
		cout << c[0] << " " << c[1] << endl;
	}

	//in.close();
	//	auto stop = high_resolution_clock::now();

	//	cout << "time is" << duration_cast<microseconds>(stop - start).count();
	return 0;
}