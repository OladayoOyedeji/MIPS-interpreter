#include <iostream>

void f()
{}

int main ()
{
    int * p = new int[10];
    std::cout << (void *)f << std::endl;
    
    return 0;
}
