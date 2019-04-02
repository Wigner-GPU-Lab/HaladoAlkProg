#include <iostream>
#include <random>
#include <chrono>
 
int main()
{
    std::random_device rd{};
    std::mt19937 gen(rd());
    
    std::uniform_real_distribution<double> distr(-1.0,1.0);

    const double pi = 3.1415926535897932384626433;

    auto t1 = std::chrono::high_resolution_clock::now();

    double sum = 0.0;
    double dsum = 0.0;
    double n = 0.0;
    double dn = 0.0;

    do
    {
        n += dn;
        sum += dsum;
        dn = dsum = 0.0;
        for(int i=0; i<100; ++i)
        {
            auto x = distr(gen);
            auto y = distr(gen);
            if(x*x+y*y <= 1.0){ dsum += 1.0; }
            dn += 1.0;
        }
    }while(std::abs(1.0 - (sum+dsum)/sum) > 1e-6);

    auto t2 = std::chrono::high_resolution_clock::now();
    
    sum = 4 * (sum + dsum) / (n + dn);
    std::cout.precision(16);
    std::cout << sum << "\n";
    std::cout << pi << "\n";
    std::cout << "Absolute error: " << std::abs(sum-pi) << "\n";

    std::cout << "Calculation took " << (static_cast<std::chrono::duration<double, std::milli>>(t2-t1)).count() << " milliseconds.\n";
    return 0;
}