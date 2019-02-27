#include <iostream>
#include <cmath>

template<typename T>
T sq(T x){ return x*x; }

template<typename F, typename T>
T integrate(F f, int n, T x0, T x1)
{
  double dx = (x1-x0)/n, sum = 0.0;
  for(int i=1; i<=n-1; i++)
  {
    sum += f(x0+i*dx);
  }
  return dx/2.0*(f(x0) + 2.0*sum + f(x1));
}
 
int main()
{
    double b = sq<double>(2.5); //6.25
    std::cout << "b = " << b << "\n";

    int    a = sq<int>(4); //16
    std::cout << "a = " << a << "\n";
    
    double b2 = sq(2.5); //6.25
    std::cout << "b2 = " << b2 << "\n";

    int    a2 = sq(4); //16
    std::cout << "a2 = " << a2 << "\n";

    double I1 = integrate([](double x){ return x*x; }, 100, 0.0, 1.0);
    double I2 = integrate(sq<double>, 100, 0.0, 1.0);
    double exact = 1.0 / 3.0;

    std::cout.precision(16);
    std::cout << "I1 = " << I1 << " exact: " << exact << " difference: " << I1 - exact << "\n";
    std::cout << "I2 = " << I2 << " exact: " << exact << " difference: " << I2 - exact << "\n";
    return 0;
}
