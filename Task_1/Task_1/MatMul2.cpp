#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>

using namespace std;

typedef vector<int> Vec;

struct Node
{
	int value;
	int row_position;
	int column_postion;
	struct Node *next;
};

void create_new_node(struct Node** start, int non_zero_element,
	int row_index, int column_index)
{
	struct Node *temp, *r;
	temp = *start;
	if (temp == NULL)
	{
		// Create new node dynamically 
		temp = (struct Node *) malloc(sizeof(struct Node));
		temp->value = non_zero_element;
		temp->row_position = row_index;
		temp->column_postion = column_index;
		temp->next = NULL;
		*start = temp;

	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;

		// Create new node dynamically 
		r = (struct Node *) malloc(sizeof(struct Node));
		r->value = non_zero_element;
		r->row_position = row_index;
		r->column_postion = column_index;
		r->next = NULL;
		temp->next = r;

	}
}

void multiply(struct Node* start, Vec v, int m)
{
	int sum = 0;
	for (int i = m; start != nullptr && i != 0; --i)
	{
		int rw = start->row_position;
		int col = start->column_postion;
		int val = start->value;
		if ((rw == start->next->row_position) && start->next->row_position != -1)
		{
				sum = sum + (val)*v[col];
				start = start->next;
		}
		else
		{
				sum = sum + (val)*v[col];
				if (sum != 0)
					cout << rw << " " << sum << endl;
				sum = 0;
				start = start->next;
		}

	}
}

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
   	//auto star = std::chrono::high_resolution_clock::now();
	//enter the dimension of the matrix
	int n;
	n = StrToInt()[0];

	//Mat A(n, vector<int>(n, 0));
	//enter the number of non-zero entries in Matrix
	int m;
	m = StrToInt()[0];

	struct Node* start = NULL;
	for (int i1 = 0; i1 < m; ++i1)
	{

		Vec numbers = StrToInt();
		int i, j, aij;
		i = numbers[0];
		j = numbers[1];
		aij = numbers[2];
		create_new_node(&start, aij, i, j);
	}
	create_new_node(&start, 0, -1, -1);

	Vec v(n, 0);
	//non zero entries in vector
	int b;
	b = StrToInt()[0];

	for (int i = 1; i <= b; ++i)
	{
		Vec numbers = StrToInt();
		int bi, vi;
		bi = numbers[0];
		vi = numbers[1];
		v[bi] = vi;
	}

	//Multiplication
	multiply(start,v,m);

	// Record end time
	/*auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - star;
	cout << "time needed is " << elapsed.count();*/
	return 0;
}