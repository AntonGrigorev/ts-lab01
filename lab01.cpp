#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

double function(double x) {
	return -cos(0.5 * x) - 1;
}


int main() {
	const double a = -2;
	const double b = 4;
	const double epsilon = 0.1;
	int N = 1;
	double x = 0;
	double delta = 0;
	std::vector<double> x_vec;
	std::vector<double> f_vec;
	std::cout << "Passive search: " << std::endl;
	do {
		for (int k = 1; k < N + 1; k++) {
			x = (b - a) / (N + 1) * k + a;
			x_vec.push_back(x);
			f_vec.push_back(function(x));
		}
		auto result = std::min_element(f_vec.begin(), f_vec.end());
		int index = std::distance(f_vec.begin(), result);
		delta = (b - a) / (N + 1);
		std::cout << "N = " << N << " " << "x = " << x_vec[index] << " +- " << delta << std::endl;
		N++;
		x_vec.clear();
		f_vec.clear();
	} while (delta > epsilon);
	std::cout << std::endl;

	std::cout << "Golden section search: " << std::endl;
	const double t = 1.618;
	double ak = a;
	double bk = b;
	double x1 = b - (b - a) / t;
	double x2 = a + (b - a) / t;
	double y1 = function(x1);
	double y2 = function(x2);
	do {
		std::cout << "ak = " << ak << " " << "bk = " << bk << " " << "|bk - ak| = " <<
			fabs(bk - ak) << " " << "f(ak) = "  << function(ak) <<
			 " " << "f(bk) = " << function(bk) <<std::endl;
		if (function(x1) < function(x2)) {
			bk = x2;
			x2 = x1;
			x1 = bk - (bk - ak) / t;
		}
		else {
			ak = x1;
			x1 = x2;
			x2 = ak + (bk - ak) / t;	
		}
	} while (fabs(bk - ak) > epsilon);
	std::cout << std::endl;
	std::cout << "ak = " << ak << " " << "bk = " << bk << " " << "Xmin = " << (ak + bk) / 2 << " +- "
		<< fabs(bk - ak) << " " << "f(ak) = " << function(ak) <<
		" " << "f(bk) = " << function(bk) << std::endl;
}
