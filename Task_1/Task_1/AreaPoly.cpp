#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

vector<int> StrToInt()
{
	vector<int> numbers;
	int enterNumber;
	string line;
	getline(cin, line);
	istringstream iss(line);
	while (iss >> enterNumber)
	{
		numbers.push_back(enterNumber);
	}
	return numbers;
}


// (X[i], Y[i]) are coordinates of i'th point. 
double polygonArea(vector<int> X, vector<int> Y, int n)
{
	// Initialze area 
	double area = 0.0;

	// Calculate value of shoelace formula 
	int j = n - 1;
	for (int i = 0; i < n; i++)
	{
		area += (X[j] + X[i]) * (Y[j] - Y[i]);
		j = i;  // j is previous vertex to i 
	}

	// Return absolute value 
	area = area/2.0;
	return fabs(area);
}

// Driver program to test above function 
int main()
{
	int n;
	n=StrToInt()[0];
	vector<int> x;
	vector<int> y;

	for (int i = 0; i < n; ++i)
	{
		vector<int> temp = StrToInt();
		x.push_back(temp[0]);
		y.push_back(temp[1]);
	}

	cout << fixed <<setprecision(1)<< polygonArea(x, y, n)<<endl;
}