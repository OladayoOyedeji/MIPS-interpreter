// File:
// Author:

#include <iostream>

int main()
{
    int x = 0;
    std::cin >> x;
    
    int y = 0;

    if (x >= 0) goto L0;
    std::cout << "bar" << std::endl;
    y = 1;
    goto L1;
    
  L0: std::cout << "foo" << std::endl;
    y = 2;
    goto L1;

  L1: return 0;
}
