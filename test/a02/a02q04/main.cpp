#include <iostream>

int main()
{
    int a, b, c, d;

    std::cin >> a >> b >> c >> d;

    a = 2 * a - c - d;
    std::cout << a << std::endl;
    
    return 0;
}
