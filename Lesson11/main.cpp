#include <vector>
#include <random>
#include <algorithm>
#include <execution>
#include <chrono>
#include <numeric>
#include <iostream>

int main()
{
	std::vector<double> v(100'000'000);
	std::mt19937 gen(0); 
	std::uniform_real_distribution<> dis(-1.0, 1.0);
	std::generate(v.begin(), v.end(), [&]{ return dis(gen); });
	std::vector<double> w = v;

	auto add = [](auto x, auto y){ return x+y; };
	auto sq = [](auto x){ return x*x; };

	auto measure = [](auto f)
	{
		auto t0 = std::chrono::high_resolution_clock::now();
		auto res = f();
		auto t1 = std::chrono::high_resolution_clock::now();
		return std::make_pair(res, (static_cast<std::chrono::duration<double, std::micro>>(t1-t0)).count());
	};
	auto policy = std::execution::par;
	auto res1 = measure( [&]{ return std::transform_reduce(        v.begin(), v.end(), 0.0, add, sq); } );
	auto res2 = measure( [&]{ return std::transform_reduce(policy, w.begin(), w.end(), 0.0, add, sq); } );

	std::cout << "Serial time: " << res1.second << " result = " << res1.first << "\n";
	std::cout << "Parallel "     << res2.second << " result = " << res2.first << "\n";
	return 0;
}