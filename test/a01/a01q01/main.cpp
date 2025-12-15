// File: main.cpp
// Author: Oladayo Oyedeji

#include <iostream>

int main()
{
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 1;
    std::cin >> a >> b >> c >> d >> e >> f >> g;
    
// Declare your temporary variables below.
// For instance if you need three temporary variables below you
// should have "int t0, t1, t2;" below this line.
// REPLACE WITH YOUR WORK for
    int t0, t1, t2;
    
// a = a + b - c * d + e * f / g ;
// Number of temporary variables: ___
    t0 = c * d;
    t1 = e * f;
    t1 = t1 / g;
    t2 = a + b;
    t0 = t2 - t0;

    a = t0 + t1;
    
    std::cout << a << ' ' << b << ' ' << c << ' '
              << d << ' ' << e << ' ' << f << ' '
              << g << " : " <<  << std::endl;
    
// The original values of b, c, d, e, f, g are preserved.
    
    return 0;
}
