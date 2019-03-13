#include <iostream>

struct Vector2d
{
	double x, y;

	Vector2d& operator+=( Vector2d const& v )
	{
		x += v.x;
		y += v.y;
		return *this;
	}
};

Vector2d operator+( Vector2d const& a, Vector2d const& b )
{
	return Vector2d{ a.x + b.x, a.y + b.y };
}

std::ostream& operator<<( std::ostream& o, Vector2d const& v )
{
	o << v.x << "   " << v.y;
	return o;
}

std::istream& operator>>( std::istream& i, Vector2d& v )
{
	i >> v.x;
	i >> v.y;
	return i;
}

int main()
{
	Vector2d v1{}, v2{};
	std::cout << "Enter vector 1:\n";
	std::cin >> v1;

	std::cout << "Enter vector 2:\n";
	std::cin >> v2;

	std::cout << "The sum of the two vectors is:\n" << v1+v2 << "\n";
	return 0;
}