#include <iostream>

int steps(int n)
{
    int num_steps = 0;

    while (n != 1)
    {
        int mask = 3;
        int r = n & mask;
        if (r == 0)
        {
            n >>= 2;
            num_steps = num_steps + 2;
        }
        else if (r == 1)
        {
            int x = n;
            n = (n << 1) + x + 1;
            n >>= 2;
            num_steps += 3;
        }
        else if (r == 2)
        {
            n >>= 1;
            int x = n;
            n = ((n << 1)) + x + 1;
            num_steps += 2;
        }
        else
        {
            int x = n;
            n = (n << 1) + x + 1;
            n >>= 1;
            num_steps += 2;
        }
        // if (n % 2 == 0)
        // {
        //     n = n  / 2;
        // }
        // else
        // {
        //     n = 3 * n + 1;
        // }
        // num_steps = num_steps + 1;
    }
    return num_steps;
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << steps(n) << std::endl;
    return 0;
}
