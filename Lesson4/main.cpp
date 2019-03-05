#include <vector>

int first(std::vector<int> const& v)
{
	return v[0];
}

int main()
{
	int n = 0;
	{
		std::vector<int> v(1'000'000'000);
		n = first(v);
	}
	return (int)n;
}
