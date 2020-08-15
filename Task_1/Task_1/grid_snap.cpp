#include<iostream>
#include<utility>
#include<vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

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

double getLowerCellPos(double x, double gw, double gwt)
{
	if (gw == 0 || gw == x)
		return x;

	if (x > gw)
		return getLowerCellPos(x, gwt + gw, gwt);

	return gw - gwt;
}

double getLowerCellNeg(double x, double gw, double gwt)
{
	if (gw == 0 || gw == x)
		return x;

	if (x < gw)
		return getLowerCellNeg(x, gwt + gw, gwt);

	return gw;
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
    
	//getting the points
    vector< pair<double,double> > point;
    for(int i=0;i<n;++i)
    {
        double x,y;
		auto numbers = StrToInt<double>();
		x = numbers[0];
		y = numbers[1];

		double x1=0.00, y1=0.00;
		if (x >= 0)
		{
			x1 = getLowerCellPos(x, gw, gw);
		}
		else
		{
			x1 = getLowerCellNeg(x, -1*gw, -1*gw);
		}

		if (y >= 0)
		{
			y1 = getLowerCellPos(y, gw, gw);
		}
		else
		{
			y1 = getLowerCellNeg(y, -1*gw, -1*gw);
		}
        point.push_back(make_pair(x1,y1));
    }
     
    //output values
    std::for_each(point.begin(),point.end(),[](pair<double,double> i){
        cout<<fixed<<setprecision(2)<<i.first<<" "<<i.second<<endl;
    });

	/*auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	cout << "time needed is " << elapsed.count();*/
    return 0;
}