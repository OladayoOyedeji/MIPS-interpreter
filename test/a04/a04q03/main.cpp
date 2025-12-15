#include <iostream>

int main()
{
    int x, y, z;
    std::cin >> x >> y >> z;

    if (x < 0 || y < 0 || z < 0)
    {
        std::cout << 0 << std::endl;
    }
    else
    {
        x = x * x;
        y = y * y;
        z = z * z;

        std::cout << (x + y == z) << std::endl;
    }
    
    return 0;
    
}
