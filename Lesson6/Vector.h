#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>

//Helper functions:
namespace detail
{
	template<typename V1, typename V2, typename F>
	void transform_vector1(V1 const& v1, V2& v2, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.begin(), f);
	}

	template<typename V1, typename V2, typename V3, typename F>
	void transform_vector2(V1 const& v1, V2 const& v2, V3& v3, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), v3.begin(), f);
	}
}

//Common lambdas:
inline auto add = [](auto const& x, auto const& y){ return x + y; };
inline auto sub = [](auto const& x, auto const& y){ return x - y; };

//Large Vector class:
//Assumptions:
//Implements a heap allocated mathematical vector
//Elements are copyable and need not to be move-aware
//No exceptional cases are not handled
template<typename T>
struct Vector
{
	std::vector<T> data;

	//Subscript operator for reading and writing:
	T&       operator()( int i )       { return data[i]; }
	T const& operator()( int i ) const { return data[i]; }

	//Function call operator for reading and writing:
	T&       operator[]( int i )       { return data[i]; }
	T const& operator[]( int i ) const { return data[i]; }

	//Default, Copy and Move constructors implemented by the compiler:
	Vector() = default;
	Vector( Vector const& ) = default;
	Vector( Vector && ) = default;

	//Copy and Move assignment operators implemented by the compiler:
	Vector<T>& operator=(Vector const&) = default;
	Vector<T>& operator=(Vector &&) = default;

	//Construct from function by passing indices from 0 to n-1:
	template<typename F>
	Vector(F f, int n)
	{
		data.resize(n);
		for(int i=0; i<n; ++i){ data[i] = f(i); }
	}
	
	//Construct from initializer list:
	Vector( std::initializer_list<T> const& il ) : data{il}{}

	//Add assignment operators:
	Vector<T>& operator+= (Vector<T> const& cpy)
	{
		detail::transform_vector2(*this, cpy, *this, add);
		return *this;
	}

	//Subtract assignment operators:
	Vector<T>& operator-= (Vector<T> const& cpy)
	{
		detail::transform_vector2(*this, cpy, *this, sub);
		return *this;
	}

	//Multiplication by scalar:
	Vector<T>& operator*= (T const& scl)
	{
		detail::transform_vector1(*this, *this, [=](T const& x){ return x * scl;} );
		return *this;
	}

	//Division by scalar:
	Vector<T>& operator/= (T const& scl)
	{
		detail::transform_vector1(*this, *this, [=](T const& x){ return x / scl;} );
		return *this;
	}

	//Number of elements of the Vector:
	int size()const
	{
		return static_cast<int>(data.size());
	}

	//begin and end for compatibility with STL:
	auto begin()
	{
		return data.begin();
	}

	auto cbegin() const
	{
		return data.cbegin();
	}

	auto end()
	{
		return data.end();
	}

	auto cend() const
	{
		return data.cend();
	}
};

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

//-------------

template<typename T>
Vector<T> operator-( Vector<T> const& v1, Vector<T> const& v2 )
{
	Vector<T> result; result.data.resize(v1.data.size());
	detail::transform_vector2(v1, v2, result, sub);
	return result;
}

template<typename T>
Vector<T>&& operator-( Vector<T>&& v1, Vector<T> const& v2 )
{
	detail::transform_vector2(v1, v2, v1, sub);
	return std::move(v1);
}

template<typename T>
Vector<T>&& operator-( Vector<T> const& v1, Vector<T>&& v2 )
{
	detail::transform_vector2(v1, v2, v2, sub);
	return std::move(v2);
}

template<typename T>
Vector<T>&& operator-( Vector<T>&& v1, Vector<T>&& v2 )
{
	detail::transform_vector2(v1, v2, v1, sub);
	return std::move(v1);
}

//dot product function does not need && versions as memory cannot be reused:
template<typename T>
T dot( Vector<T>const& v1, Vector<T>const& v2)
{
	return std::inner_product(v1.cbegin(), v1.cend(), v2.cbegin(), static_cast<T>(0));
}

//sqlength function does not need && versions as memory cannot be reused:
template<typename T>
T sqlength( Vector<T>const& v )
{
	return std::accumulate(v.cbegin(), v.cend(), static_cast<T>(0), [](T const& acc, T const& x){ return acc + x*x; });
}

//length function does not need && versions as memory cannot be reused:
template<typename T>
T length( Vector<T>const& v )
{
	return std::sqrt(sqlength(v));
}

//normalize, scalar multiplication, division needs two versions as they have one vector argument where memory can be reused:
template<typename T>
Vector<T> operator*(Vector<T> const& v, T const& scl)
{
	Vector<T> result; result.data.resize(v.data.size());
	detail::transform_vector1(v, result, [=](T const& x){ return x * scl; });
	return result;
}

template<typename T>
Vector<T>&& operator*(Vector<T>&& v, T const& scl)
{
	detail::transform_vector1(v, v, [=](T const& x){ return x * scl; });
	return std::move(v);
}

template<typename T>
Vector<T> operator*(T const& scl, Vector<T> const& v)
{
	Vector<T> result; result.data.resize(v.data.size());
	detail::transform_vector1(v, result, [=](T const& x){ return scl * x; });
	return result;
}

template<typename T>
Vector<T>&& operator*(T const& scl, Vector<T>&& v)
{
	detail::transform_vector1(v, v, [=](T const& x){ return scl * x; });
	return std::move(v);
}

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

template<typename T>
Vector<T> normalize(Vector<T> const& v)
{
	return v / length(v);
}

template<typename T>
Vector<T>&& normalize(Vector<T>&& v)
{
	auto l = length(v);
	return std::move(v) / l;
}

template<typename T>
std::ostream& operator<< (std::ostream& o, Vector<T> const& v)
{
	int n = v.size();
	if( n > 0 )
	{
		for(int i=0; i<n-1; ++i)
		{
			std::cout << v[i] << "   ";
		}
		std::cout << v[n-1];
	}
	return o;
}