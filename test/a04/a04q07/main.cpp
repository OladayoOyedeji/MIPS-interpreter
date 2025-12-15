#include <iostream>

int main()
{
    int x, y;
    std::cin >> x >> y;
    int sum = x + y;
    std::cout << "  " << x / 10 << " " << x % 10 << std::endl;
    std::cout << "+ " << y / 10 << " " << y % 10 << std::endl;
    std::cout << "------";
    if (sum > 99)
        std::cout << sum / 100;
    else
        std::cout << " ";
    std::cout << " "
              << sum / 10 % 10 << " "
              << sum % 10 << std::endl;
    std::cout << "--------"
    
    return 0;
}
