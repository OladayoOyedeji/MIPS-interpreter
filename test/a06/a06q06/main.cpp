#include <iostream>
#include <cstdlib>
#include <cmath>

const char * itoa(int value, char * string, int radix)
{
    if  (value == 0)
    {
        string[0] = '0';
        string[1] = '\0';
        return string;
    }
    int i = 0;
    if (value < 0)
    {
        string[i++] = '-';
        value *= -1;
    }
    int n = value;
    int size = 0;
    while(n != 0)
    {
        n /= 10;
        size++;
    }
    for (int j = size - 1; j >= 0; --j)
    {
        string[i++] = '0' + value / int(pow(10, j)) % 10;
    }
    string[i] = '\0';
    return string;
}

int main()
{
    char s[100] = "";

    std::cout << int('0') << std::endl;
    std::cout << itoa(-42, s, 10) << std::endl;
    std::cout << s << std::endl;

    std::cout << itoa(42, s, 10) << std::endl;
    std::cout << s << std::endl;

    std::cout << itoa(0, s, 10) << std::endl;
    std::cout << s << std::endl;

    return 0;
}
