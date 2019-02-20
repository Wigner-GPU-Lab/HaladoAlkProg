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

 
int main()
{
    solve(612.0, 15.0);
    std::cout << length(1.0, 2.0, 3.0) << "\n";
    return 0;
}