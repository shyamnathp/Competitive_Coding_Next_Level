#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;

typedef vector<int> Vec;
typedef vector<vector<int>> Mat;

vector<int> StrToInt()
{
	Vec numbers;
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
	// Record start time
	auto start = std::chrono::high_resolution_clock::now();
    //enter the dimension of the matrix
    int n;
	n = StrToInt()[0];

	Mat A(n, vector<int>(n, 0));
    //enter the number of non-zero entries in Matrix
    int m;
    m= StrToInt()[0];
    for(int i1=0;i1<m;++i1)
    {
		
		Vec numbers = StrToInt();
        int i,j,aij;
		i = numbers[0];
		j = numbers[1];
		aij = numbers[2];
	
		A[i][j] = aij;
    }

    Vec v(n,0);
    //non zero entries in vector
    int b;
    b= StrToInt()[0];

    for(int i=1;i<=b;++i)
    {
		Vec numbers = StrToInt();
        int bi,vi;
        bi=numbers[0];
        vi=numbers[1];
        v[bi]=vi;
    }

    //Multiplication
    for(int i=0;i<n;++i)
    {
    //   auto sp = std::inner_product(A[i].begin(),A[i].end(),v.begin(),0);
     //   Av.push_back(Avec);
		int sp = 0,j=0;
		for_each(A[i].begin(), A[i].end(), [&sp,&j,v](int a)
		{ 
			if (a != 0)
			{
				sp = sp + a * v[j];
			}
			++j;
		});
     
		if(sp!=0)
			cout << i << " " << sp<<endl;

    }
     
	// Record end time
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	cout << "time needed is " << elapsed.count();
return 0;
}