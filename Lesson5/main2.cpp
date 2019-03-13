#include <iostream>

template<typename T>
struct Vector2
{
	T x, y;

	Vector2<T>& operator+=( Vector2<T> const& v )
	{
		x += v.x;
		y += v.y;
		return *this;
	}
};

template<typename T>
Vector2<T> operator+( Vector2<T> const& a, Vector2<T> const& b )
{
	return Vector2<T>{ a.x + b.x, a.y + b.y };
}

template<typename T>
std::ostream& operator<<( std::ostream& o, Vector2<T> const& v )
{
	o << v.x << "   " << v.y;
	return o;
}

template<typename T>
std::istream& operator>>( std::istream& i, Vector2<T>& v )
{
	i >> v.x;
	i >> v.y;
	return i;
}

int main()
{
	Vector2<double> v1{}, v2{};
	std::cout << "Enter vector 1:\n";
	std::cin >> v1;

	std::cout << "Enter vector 2:\n";
	std::cin >> v2;

	std::cout << "The sum of the two vectors is:\n" << v1+v2 << "\n";
	return 0;
}