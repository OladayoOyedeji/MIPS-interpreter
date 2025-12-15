// file: main.cpp (for testing seven_seg.h)

#include <iostream>
#include <vector>
#include <boost/range/combine.hpp>
#include "seven_seg.h"

int main()
{
    seg7_t blank = seg7({0,0,0,0,0,0,0});
    seg7_t neg = seg7({0,0,0,1,0,0,0});
    seg7_t one = seg7({0,0,1,0,0,1,0});
    seg7_t two = seg7({1,0,1,1,1,0,1});
    seg7_t six = seg7({1,1,0,1,1,1,1});
    seg7_t seven = seg7({1,0,1,0,0,1,0});
    seg7_t o = seg7({0,0,0,1,1,1,1});
    seg7_t r = seg7({0,0,0,1,1,0,0});
    seg7_t E = seg7({1,1,0,1,1,0,1});
    seg7array({blank, blank, blank, blank, blank, blank, blank, blank,
               neg, one, two, seven, blank, o, r, E}
        );
    return 0;
}
