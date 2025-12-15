#include <iostream>

int passfail(int flag)
{
    if (flag == 0)
    {
        std::cout << "FAIL";
        return 0;
    }
    else
    {
        std::cout << "pass";
        return 1;
    }
    
}

int main()
{
    const int NUM_TESTS = 5;
    char s[NUM_TESTS][100] = {"hello world",
        "a",
        "",
        "hello\0 world",
        "ABCDEFGHIJKL"};

    int correct[NUM_TESTS] = {11, 1, 0, 5, 12};
    int numerrs = 0;

    for (int i = 0; i < NUM_TESTS; ++i)
    {
        std::cout << "Test " << i << ": ";
        numerrs += passfail(strlen(s[i]) == correct[i]);
        std::cout << std::endl;
    }

    std::cout << "TOTAL NUMBER OF TEST CASES: " << NUM_TESTS
              << std::endl
              << "TOTAL NUMBER OF ERRORS: " numerrs << std::endl;
    
    return 0;
}
