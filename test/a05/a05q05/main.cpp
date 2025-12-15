#include <iostream>

void bubblesort()
{
    for (int * q = end - 2; q > start; --q)
    {
        for (int * p = start; p <= q; ++p)
        {
            if (*p > *(p + 1))
            {
                swap();
            }
        }
    }
}
