#include <iostream>

int main()
{
    int x;
    std::cin >> x;

    int year = x / 10000;
    int month = x / 1000 % 10;
    int day = x % 100;
    
    switch (month)
    {
        case 4:
        case 6:
        case 9:
        case 11:
            if (day > 30)
                std::cout << 0 << std::endl;
            else
                std::cout << 1 << std::endl;
            break;
        case 2:
            if (day > 29) std::cout << 0 << std::endl;
            
            else if (year % 4 == 0 && year % 100 != 0 && day == 29)
            {
                std::cout << (day <= 29) << std::endl;
            }
            else std::cout << 1 << std::endl;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (day > 31)
                std::cout << 0 << std::endl;
            else
                std::cout << 1 << std::endl;
    }
    return 0;
}
