#include<iostream>
#include<utility>
#include<vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

template<typename T>
vector<T> StrToInt()
{
	vector<T> numbers;
	T enterNumber;
	string line;
	getline(cin, line);
	istringstream iss(line);
	while (iss >> enterNumber)
	{
		numbers.push_back(enterNumber);
	}
	return numbers;
}

double OtherCase(double num, double gw)
{   
	double x1 = 0;

	if (num >= 0)
		x1 = 100000;
	else
		x1 = 10000 - gw;

	return x1;
}

double getLowerCellPos(double x, double gw)
{
		int div = x / gw;
		double gpos = div * gw;
		return gpos;
}

int main()
{
	//	auto start = std::chrono::high_resolution_clock::now();

		//number of points
	int n;
	n = StrToInt<int>()[0];
	//grid width
	double gw;
	gw = StrToInt<double>()[0];
	gw = gw * 100;
	int temp = ((10000 * 100) / (gw));
	double mov = (temp * gw) + gw;
	//getting the points
	vector< pair<double, double> > point;
	for (int i = 0; i < n; ++i)
	{
		double x, y;
		auto numbers = StrToInt<double>();
		x = numbers[0]*100 + mov;
		y = numbers[1]*100 + mov;

		double x1 = 0.00, y1 = 0.00;
		if (gw == 0.00)
		{
			x1 = x;
			y1 = y;
		}
		else
		{
			if ((gw / 100) > numbers[0] && numbers[0] >= 0)
			{	//x1 = OtherCase(numbers[0], gw/100);
				x1 = mov;
			}
			else
			{
				x1 = getLowerCellPos(x, gw);
			}

			if ((gw / 100) > numbers[1] && numbers[1] >= 0)
			{
				y1 = mov;
			}
			else
			{
				y1 = getLowerCellPos(y, gw);
			}
		}
		point.push_back(make_pair((x1 - mov)/100, (y1 - mov)/100));
	}

	//output values
	std::for_each(point.begin(), point.end(), [](pair<double, double> i) {
		cout << fixed << setprecision(2) << i.first << " " << i.second << endl;
	});

	/*auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	cout << "time needed is " << elapsed.count();*/
	return 0;
}