#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>

template<typename T>
struct Vector
{
	std::vector<T> data;

	T&       operator()( int i )       { return data[i]; }
	T const& operator()( int i ) const { return data[i]; }

	T&       operator[]( int i )       { return data[i]; }
	T const& operator[]( int i ) const { return data[i]; }

	Vector() = default;
	Vector( Vector const& ) = default;
	Vector( Vector && ) = default;

	Vector<T>& operator=(Vector const&) = default;
	Vector<T>& operator=(Vector &&) = default;

	//construct from function by passing indices:
	template<typename F>
	Vector(F f, int n)
	{
		data.resize(n);
		for(int i=0; i<n; ++i){ data[i] = f(i); }
	}
	
	//construct from initializer list:
	Vector( std::initializer_list<T> const& il ) : data{il}{}
};

namespace detail
{
	template<typename V1, typename V2, typename F>
	void transform_vector1(V1 const& v1, V2& v2, F f)
	{
		std::transform(v1.data.begin(), v1.data.end(), v2.data.begin(), f);
	}

	template<typename V1, typename V2, typename V3, typename F>
	void transform_vector2(V1 const& v1, V2 const& v2, V3& v3, F f)
	{
		std::transform(v1.data.begin(), v1.data.end(), v2.data.begin(), v3.data.begin(), f);
	}
}

auto add = [](auto const& x, auto const& y){ return x + y; };

//Addition operators 4 versions for all combinations of const& and &&:
//Same applies to the two argument operator-
template<typename T>
Vector<T> operator+( Vector<T> const& v1, Vector<T> const& v2 )
{
	Vector<T> result; result.data.resize(v1.data.size());
	detail::transform_vector2(v1, v2, result, add);
	return result;
}

template<typename T>
Vector<T>&& operator+( Vector<T>&& v1, Vector<T> const& v2 )
{
	detail::transform_vector2(v1, v2, v1, add );
	return std::move(v1);
}

template<typename T>
Vector<T>&& operator+( Vector<T> const& v1, Vector<T>&& v2 )
{
	detail::transform_vector2(v1, v2, v2, add );
	return std::move(v2);
}

template<typename T>
Vector<T>&& operator+( Vector<T>&& v1, Vector<T>&& v2 )
{
	detail::transform_vector2(v1, v2, v1, add );
	return std::move(v1);
}

//dot product function does not need && versions as memory cannot be reused:
//similarly length, sqlength can be defined
template<typename T>
T dot( Vector<T>const& v1, Vector<T>const& v2)
{
	return std::inner_product(v1.begin(), v1.end(), v2.begin());
}

//normalize, scalar multiplication, division needs two versions as they have one vector argument:
template<typename T>
Vector<T> operator/(Vector<T> const& v, T const& scl)
{
	Vector<T> result; result.data.resize(v.data.size());
	detail::transform_vector1(v, result, [=](T const& x){ return x / scl; });
	return result;
}

template<typename T>
Vector<T>&& operator/(Vector<T>&& v, T const& scl)
{
	detail::transform_vector1(v, v, [=](T const& x){ return x / scl; });
	return std::move(v);
}

#include <iostream>
int main()
{
    Vector<double> v{{1., 2., 3.}};
    Vector<double> u{{10., 20., 30.}};
    auto w = (v + std::move(u)) / 2.0;
    std::cout << w[0] << "\n";
}