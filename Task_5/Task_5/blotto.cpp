#include <iostream> 
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

//uses dynamic programming to find all the combinations of length b that add to num
//doesnot consider permutations cos the values are stored in increasing order
void findCombinationsUtil(vector<int>& arr, int index,
	int num, int reducedNum, int b, vector<vector<int>>& comb)
{
	if (reducedNum < 0)
		return;

	if (reducedNum == 0)
	{
		if (index <= b)
		{
			//arr.resize(b,0);
			//for (int i = 0; i < index; i++)
			//  cout << arr[i] << " ";
			 
			comb.push_back(arr);
			//cout << endl;
		}
		return;
	}
 
	int prev = (index == 0) ? 1 : arr[index - 1];

	for (int k = prev; k <= num; k++)
	{
		if (index >= (b))
	    	break;

		if (k == num)
			arr[index] = 0;
		else
			arr[index] = k;
		findCombinationsUtil(arr, index + 1, num,
			reducedNum - k, b, comb);
	}
}

//comb will contain all the combinations
vector<vector<int>> findCombinations(int n, int b)
{
	vector<int> arr(b,0);
	vector<vector<int>> comb;

	findCombinationsUtil(arr, 0, n, n, b, comb);

	int siz = comb.size();
	comb[siz - 1][b-1] = n;

	return comb;
}


//creating the payoff matrix. i compute the permutations of the each of General's strategy and compare it with tsu's strateg
//and updates sum, which is used to store the number of wars won by sun tzu.
//it returns a (sum * (bfac / iter)) because sometimes the colomn can have repeated values, like 110(b=3), here the 
//number of permutations is not 6 and its 3. To make it 6 for all cases, i do a 3 * (bfac/iter) = 3*(3!/2) = 6
//i dont have to consider separate perumations of tsu because its the ratio that we want and if we did consider them, it will be
// an *bfac for both denom and numerator.
int payoff(vector<int>& t, vector<int>& c, int bfac, int& totalwars)
{
	int sum = 0;
	int iter = 0;

	do
	{
		++iter;
		int tempsum = 0;
		for (int i = 0; i < t.size(); ++i)
		{
			if (t[i] > c[i])
			{
				tempsum = tempsum + 1;
			}
			else if (t[i] < c[i])
			{
				tempsum = tempsum - 1;
			}
		}

		if (tempsum > 0)
		{
			sum = sum + 1;
		}
		/*else if (tempsum < 0)
		{
			sum = sum - 1;
		}*/
	} while (std::next_permutation(c.begin(), c.end()));

	totalwars = totalwars + iter;

	//return (sum * (bfac / iter));
	return sum;
}

int factorial(int n)
{
	// single line to find factorial 
	return (n == 1 || n == 0) ? 1 : n * factorial(n - 1);
}


//sum have the number of wars won. Total number of wars done for one strategy of tsu is col.size() * number of permutation for each
void Blotto(vector<vector<int>>&tzu , vector<vector<int>>& col, int b)
{
	int bfac = factorial(b);
	double mVal = 0;
	
	for (auto& t : tzu)
	{   
		int totalwars = 0;
		double sum = 0;
		for (auto& c : col)
		{
		//	std::sort(c.begin(), c.end());
			sum = sum + payoff(t,c,bfac,totalwars);
		//	std::sort(c.begin(), c.end());
			
		}
		cout << sum << endl;
		mVal = max(sum, mVal);
	}

	//cout << fixed <<setprecision(3)<< (mVal/(col.size() * bfac));
}


int main()
{
	int n, n1, b;
	cin >> n >> n1 >> b;
	vector<vector<int>> tzu, col;
	
	if (b == 1)
	{
		if (n > n1)
			cout << "1.000";
		else
			cout << "0.000";
	}
	else
	{
		tzu = std::move(findCombinations(n, b));
		col = std::move(findCombinations(n1, b));
		Blotto(tzu, col, b);
	}

	/*vector<int> myints = { 0,1,1 };
	std::sort(myints.begin(), myints.end());
	do
	{
		std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';
	} while (std::next_permutation(myints.begin(), myints.end())); */
	return 0;
}