#include <iostream>

void DFA(int input[], int n)
{
    int state = 0;
    for (int i = 0; i < n; ++i)
    {
        int val = input[i];
        switch (state)
        {
            case 0:
            {
                switch (val)
                {
                    case 2: state = 1; break;
                    case 3: state = 0; break;
                }
            }
            case 1:
            {
                switch (val)
                {
                    case 2: state = 1; break;
                    case 3: state = 0; break;
                }
            }
        }
    }
    std::cout << state << std::endl;
}

int main()
{
    int n;
    std::cin >> n;

    const int size = n;
    int input[size];
    for (int i = 0; i < n; ++i)
    {
        std::cin >> input[i];
    }

    DFA(input, n);
    
    return 0;
}
