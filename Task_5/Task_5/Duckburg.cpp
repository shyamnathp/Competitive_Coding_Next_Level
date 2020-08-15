#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
#include <iterator>
#include <cmath>
#include <set>
#include <numeric>

using namespace std;

int findMedian(set<int>& a, int n)
{
	std::set<int>::iterator it2 = a.begin();

	// check for even case 
	if (n % 2 != 0)
	{
		std::advance(it2, (a.size()) / 2);
		return (*it2);
	}

	std::advance(it2, a.size() / 2);
	int i1 = *it2;
	int i2 = *(prev(it2));
	return (i1 + i2) / 2.0;
}

int main()
{
	std::ifstream in("p103.t2.in");

	int i1, n;
	in >> i1 >> n;

	map<int, int> valueN;
	//map<int, int>::iterator i = valueN.begin();

	for(int i=0; i<n; ++i)
	{
		int val;
		in >> val;
		valueN.insert(make_pair(val,0));
	}

	for (auto it= valueN.begin();it!=valueN.end();++it)
	{
		if (it == valueN.begin())
		{
			it->second = 1001;
			next(it)->second = next(it)->first - it->first;
		}
		else if(it == prev(valueN.end()))
		{
			it->second = it->first - prev(it)->first;
		}
		else
		{
			it->second = it->first - prev(it)->first;
			next(it)->second = next(it)->first - it->first;
		}
	}

	int final = 0;
	int temp=1;
	set<int> all;

	for (int i = 0; i < (n - i1); ++i)
	{
		auto it = min_element(valueN.begin(), valueN.end(),
			[](decltype(valueN)::value_type& l, decltype(valueN)::value_type& r) -> bool { return l.second < r.second; });

		all.insert(it->first);
		it->second = 1001;
	}

	set<int> tempVal;
	map<int, int>::iterator it1 = valueN.begin();
	for (auto it = all.begin(); it != all.end(); ++it, ++it1)
	{
		if (*it == it1->first)
		{
			tempVal.insert(it1->first);
		}
		else
		{
			int avg = 0;
			//int median = 0;
			if (tempVal.size() != 0)
			{
				/*int mv = 0;
				if (tempVal.size() % 2 != 0)
				{
					mv = (tempVal.size() + 1)/2;
				}
				else
				{
					mv = tempVal.size() / 2;
				}*/
				//std::set<int>::iterator it2 = tempVal.begin();
				//std::advance(it2, tempVal.size() / 2);
				//avg = *it2;

				avg = findMedian(tempVal, tempVal.size());
			}
			//	avg = std::accumulate(tempVal.begin(), tempVal.end(), 0) / tempVal.size();

			for (auto& it : tempVal)
			{
				final = final + abs(it - avg);
			}
			tempVal.clear();

			it1 = valueN.find(*it);

			tempVal.insert(prev(it1)->first);
			tempVal.insert(it1->first);

		}
	}


	if (!tempVal.empty())
	{
		int avg = 0;
		//std::set<int>::iterator it2 = tempVal.begin();
		//std::advance(it2, tempVal.size() / 2);
		//avg = *it2;
		avg = findMedian(tempVal, tempVal.size());

		for (auto& it : tempVal)
		{
			final = final + abs(it - avg);
		}
	}

	int finVal = 25 * n - final;
	cout << finVal;
	return 0;
}