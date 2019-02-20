#include <iostream>
#include <math.h>

double sq(double x)
{
    return x*x;
}

double length(double x, double y, double z)
{
  return std::sqrt(sq(x)+sq(y)+sq(z));
}

double distance(double x1, double y1, double z1,
                double x2, double y2, double z2)
{
  return std::sqrt( sq(x1-x2) + sq(y1-y2) + sq(z1-z2) );
}

//solve a*x+b = 0
void solve(double a, double b)
{
  std::cout << "Solving equation: " << a << "*x + " << b << " = " << 0 << "\n";
  if( a == 0.0 )
  {
    std::cout << "No solution\n";
  }
  else
  {
    std::cout << "The solution is: " << -b/a << "\n";
  }
}

double sum_of_squares(int n)
{
  double sum = 0.0;
  for(int i=0; i<=n; ++i)
  {
    sum += sq(i);
  }
  return sum;
}


//solve a*x*x+b*x+c = 0
void solve(double a, double b, double c)
{
  std::cout << "Solving equation: " << a << "*x^2 + " << b << "*x + " << c << " = " << 0 << "\n";
  if( double sqb = sq(b), discr = sqb-4.0*a*c; discr < 0.0 )
  {
    std::cout << "No solution\n";
  }
  else if(discr == 0.0)
  {
    std::cout << "There is one solution: " << -b / (2.0*a) << "\n";
  }
  else
  {
    double sqrt_discr = std::sqrt(discr);
    std::cout << "The two solutions are: " << (-b + sqrt_discr)/(2.0*a) << " and " << (-b - sqrt_discr)/(2.0*a) << "\n";
  }
}

 
int main()
{
    solve(2.0, 20.0);
    solve(4.0, -5.0, 1.0);
    std::cout << "Length of vector: " << length(1.0, 1.0, 2.0) << "\n";
    return 0;
}
