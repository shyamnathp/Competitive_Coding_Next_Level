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
	bool operator()(const vector<string>& i1, const vector<string>& i2) const {
		return (i1.size() < i2.size());
	}
};

void findFriends(vector<vector<string>>& houses, set<string>& Friends, set<string>& notFriends)
{
	for (auto it = houses.begin(); it != houses.end(); ++it)
	{
		if (it->size() == 2)
		{
			if (*(prev(it->end())) == "odd")
			{
				Friends.insert(it->begin(), prev(it->end()));
			//	houses.erase(it);
			}
			else
			{
				notFriends.insert(it->begin(), prev(it->end()));
			//	houses.erase(it);
			}
		}

		for (auto it1 = next(it); (it1 != houses.end()) && ((it1->size()) <= (it->size() + 1)); it1++)
		{
			if (std::includes(it1->begin(), prev(it1->end()), it->begin(), prev(it->end())))
			{

				//string val = *(prev(it->end())) + *(prev(it1->end()));

				vector<string> result;

				auto it2 = set_difference(it1->begin(), prev(it1->end()), it->begin(), prev(it->end()), std::inserter(result, result.end()));


				if (*(prev(it->end())) != *(prev(it1->end())))
				{
					Friends.insert(result.begin(), result.end());
				//	houses.erase(it);
				}
				else
				{
					notFriends.insert(result.begin(), result.end());
				//	houses.erase(it);
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

	vector<vector<string>> houses;

	//cin.ignore(256, '\n');
	string l;
	getline(in, l);

	for (int j = 0; j < n; ++j)
	{
		string line;
		getline(in, line);
		istringstream iss(line);
		string word;
		//int oddEven;

		vector<string> setTemp;

		while (iss >> word)
		{
			setTemp.push_back(word);
		}

		std::sort(setTemp.begin(), prev(setTemp.end()));

		houses.push_back(setTemp);
	}

	std::sort(houses.begin(), houses.end(),
		[](const std::vector<string>& a, const std::vector<string>& b) {
		return a.size() < b.size();
	});

	//std::sort(houses.begin(), houses.end(), compareSize);

	set<string> Friends, notFriends;

	while ((Friends.size() + notFriends.size()) != n)
	{
		findFriends(houses, Friends, notFriends);

		//vector<vector<string>> houses1;
		for (auto it = houses.begin(); it != houses.end(); it++)
		{
			vector<string> v;
			auto it2 = set_difference(it->begin(), prev(it->end()), notFriends.begin(), notFriends.end(), std::inserter(v, v.end()));
			v.push_back(*(prev(it->end())));
			*it = v;
		}

		std::sort(houses.begin(), houses.end(),
			[](const std::vector<string>& a, const std::vector<string>& b) {
			return a.size() < b.size();
		});


		//houses.erase(it);
		houses.erase(unique(houses.begin(), houses.end()), houses.end());

		//houses.clear();
		//houses = std::move(houses1);
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