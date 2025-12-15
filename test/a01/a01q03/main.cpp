// File: main.cpp
// Author: Oladayo Oyedeji

#include <iostream>

int main()
{
    int x = 0;
    std::cin >> x;

    int i = 0;
  L0: if (i >= x) goto L3;
    std::cout << i << std::endl;
    i = i + 1;
    goto L0;

  L3: return 0;

    
}
