
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>
#include <fstream>
#include <cmath>
#include <complex>
#include <set>
#include <array>

using namespace std;

int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i)
	{ 
		double u, v, w;
		double k;
		double p, q;
		double a, b, c;
		cin >> u >> v >> w;
		k = (u*u - w) / 2;

		a = -u;
		b = k;
		c = -v;

		p = -(a * a / 3.0) + b;
		q = (2.0 / 27.0 * a * a * a) - (a * b / 3.0) + c;

		double d;
		d = q * q / 4.0 + p * p * p / 27.0;;

		double shift = (1. / 3)*a;

		if (d < 0)
		{
		 	std::complex<double> u(q, 0), rt[3];
			u = pow(-0.5*u - sqrt(0.25*u*u + p*p*p / 27), 1. / 3);
			rt[0] = u - p / (3.*u) - shift;
			std::complex<double> w(-0.5, sqrt(3.) / 2);
			rt[1] = u * w - p / (3.*u*w) - shift;
			rt[2] = u / w - p * w / (3.*u) - shift;

			std::array<int, 3> roots;
			for (int i = 0; i < 3; ++i)
			{
				roots[i] = static_cast<int>(round(rt[i].real()));
			}

			std::sort(roots.begin(),roots.end());
			
			cout << roots[0] <<" "<< roots[1] <<" "<< roots[2] <<endl;
		}
		else
		{
			cout << "empty set" << endl;
		}

	}

	return 0;
}