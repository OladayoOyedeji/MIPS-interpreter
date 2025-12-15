#include <iostream>

int main()
{
    for (int i = 0;i < 4; ++i)
    {
        if (x[i] > max)
        {
            second_max = max;
            max = x[i];
        }
        else if (x[i] > second_max)
        {
            second_max = x[i];
        }
    }
    std::cout << second_max << std::endl;
    
    return 0;
}
