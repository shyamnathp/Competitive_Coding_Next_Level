#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <set>
#include <map>
#include <iterator>
#include <list>

using namespace std;

struct compareSize {
	bool operator()(const set<string> i1,const set<string> i2) const{
		return (i1.size() < i2.size());
	}
};

void findFriends(multimap<set<string>, int, compareSize>& houses, set<string>& Friends, set<string>& notFriends)
{
	for (auto it = houses.begin(); it != prev(houses.end()); it++)
	{
		if (it->first.size() == 1)
		{
			if (it->second == 0)
			{
				Friends.insert(it->first.begin(), it->first.end());
				break;
			}
			else
			{
				notFriends.insert(it->first.begin(), it->first.end());
			}
		}

		for (auto it1 = next(it); (it1 != houses.end()) && ((it1->first.size()) <= (it->first.size() + 1)); it1++)
		{
			if(std::includes(it1->first.begin(), it1->first.end(), it->first.begin(), it->first.end()))
			{
				//cout << "true" << endl;
			/*	for (auto& i : it->first)
				{
					cout << i << " ";
				}
				cout << it->second << " and ";

				for (auto& i : it1->first)
				{
					cout << i << " ";
				}
				cout << it1->second << endl; */

				//string s = it->second + it1->second;

				int val = it->second * 10 + it1->second;

				std::set<string> result;
			/*	std::vector<string> v1;
				v1.assign(it1->first.begin(), it1->first.end());
				std::vector<string> v2;
				v2.assign(it->first.begin(), it->first.end()); */
		 
			//	auto it2 = set_difference(v1.begin(), v1.end(),v2.begin(), v2.end(), v);
				auto it2 = set_difference(it1->first.begin(), it1->first.end(), it->first.begin(), it->first.end(), std::inserter(result, result.end()));

				switch (val)
				{
				case 0: notFriends.insert(result.begin(), result.end());
						break;
				case 10: Friends.insert(result.begin(), result.end());
						break;
				case 1: Friends.insert(result.begin(), result.end());
					    break;
				case 11:notFriends.insert(result.begin(), result.end());
						break;
				}

			}
		}
	}
}

int main()
{
	std::ifstream in("p103.t2.in");

	int n;
	in >> n;

	multimap<set<string>, int, compareSize> houses;

	//cin.ignore(256, '\n');
	string l;
	getline(in, l);

	for (int j = 0; j < n; ++j)
	{
		string line;
		getline(in, line);
		istringstream iss(line);
		string word;
		int oddEven;

		set<string> setTemp;
		while (iss >> word)
		{
			if (word == "odd")
			{
				oddEven = 0;
				break;
			}
			else
		    if (word == "even")
			{
				oddEven = 1;
				break;
			}
			else
			{
				setTemp.insert(word);
			}
		}

		houses.insert(make_pair(setTemp,oddEven));
	}

	//std::sort(houses.begin(), houses.end(), compareSize);

	set<string> Friends, notFriends;

	while ((Friends.size() + notFriends.size()) != n)
	{
		findFriends(houses, Friends, notFriends);

		multimap<set<string>, int, compareSize> houses1;
		for (auto it = houses.begin(); it != houses.end(); it++)
		{
			set<string> v;
			auto it2 = set_difference(it->first.begin(), it->first.end(), notFriends.begin(), notFriends.end(), std::inserter(v, v.end()));
			houses1.insert(make_pair(v, it->second));
		}

		houses.clear();

		while (houses1.size() > 0)
		{
			auto element = *(houses1.begin());
			houses.insert(make_pair(element.first, element.second));
			houses1.erase(element.first);
		}

	}

	cout << Friends.size();

	/*for (auto it = houses.begin(); it != houses.end(); it++)
	{
		//cout << it->second << endl;
		for (auto& i : it->first)
		{
			cout << i << " ";
		}
		cout << it->second <<endl;
	}*/
	return 0;
}