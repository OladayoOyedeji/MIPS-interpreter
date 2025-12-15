#include <iostream>

int main()
{
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    std::cout << a * b + (b - c) / a % d;
    
    return 0;
}
