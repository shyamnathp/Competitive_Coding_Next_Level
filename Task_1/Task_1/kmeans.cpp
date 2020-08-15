#include <iostream>
#include <vector>
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

int main()
{
	int n;
	n = StrToInt()[0];
	
	double sum = 0;
	for (int i = 0; i < n; ++i)
	{
		vector<int> numbers = StrToInt();
		sum = sum + (pow(numbers[0], 2) + pow(numbers[1], 2));
	}

	cout << fixed << setprecision(30) << sum << endl;
	return 0;
}