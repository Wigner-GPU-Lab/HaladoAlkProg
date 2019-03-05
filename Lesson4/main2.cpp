#include <iostream>
#include <vector>
#include <numeric>

int main()
{
	std::vector<double> B = {1.0, 2.0, 3.0};
	
	double n = 4.0;
	auto f = [n](double a, double b){ return a + std::pow(b, n); };

	auto s = std::accumulate(B.begin(), B.end(), 0.0, f);

	std::cout << "sum b^n: " << s << "\n";
	return 0;
}