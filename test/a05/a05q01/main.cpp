#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    std::cout << n = 9 << ' ';
    int sum = 0;
    sum += n / 1000 % 10;
    sum += n / 100 % 10;
    sum += n / 10 % 10;
    sum += n % 10;

    std::cout << sum << ' ' << sum % 9 << std::endl;
        
    return 0;
}
