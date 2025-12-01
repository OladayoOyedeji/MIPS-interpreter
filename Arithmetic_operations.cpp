#include "Arithmetic_operations.h"

void half_adder(word * s, word * c, word x, word y)
{
    *s = (~x & y) | (x & ~y);

    *c = x & y;
    
}
void bit_adder(word * s, word * c, word x, word y, word z)
{
    word c0;
    word c1;
    word s0;
    half_adder(&s0, &c0, x, y);
    half_adder(s, &c1, s0, z);
    *c = c0 | c1;
}

void readbits(word * x)
{
    *x = 0;
    std::string s;
    std::cin >> s;
    auto p = s.begin();
    for (int i = 0; i < s.size(); ++i)
    {
        *x = (*x << 1) | (*p++ == '0' ? 0 : 1);
        // int b = (*p++ == '0' ? 0 : 1);
        // *x |= (b << i);
        
    }
}

void readbit(word * x)
{
    std::string s;
    std::cin >> s;
    std::cout << s << std::endl;
    int b = (s[0] == '0' ? 0 : 1);
    *x |= b;
}

void printbits(word x)
{
    for (int i = 31; i >= 0; --i)
    {
        std::cout << ((x >> i) & 1);
    }
    std::cout << ' ' << x; 
    std::cout << '\n';
}

void printbit(word x)
{
    std::cout << (x & 1) << '\n'; 
}

bit addu(word * ret, word x, word y)
{
    bit c = 0;
    *ret = 0;
    for (int i = 0; i < 32; ++i)
    {
        
        bit c_i  = 0;
        bit s_i = 0;
        bit_adder(&s_i, &c_i, c, (x & 1), (y & 1));
        x >>= 1;
        y >>= 1;
        c = c_i;
        *ret |= (s_i << i);
    }
    return c;
}

void subu (word * ret, word x, word y)
{
    // ret = x + (2^32 - y)
    printbits(x);
    printbits(y);
    addu(ret, x, (~y + 1));
}

void multu(word * HI, word * LO, word x, word y)
{
    *HI = 0;
    *LO = 0;
    word hi, lo;
    lo = x;
    hi = 0;
    printbits(x);
    printbits(y);
    for (int i = 0; i < 64; ++i)
    {
        bit c = addu(LO, *LO, lo * (y & 1));
        hi <<= 1;
        hi |= (lo >> 31);
        lo <<= 1;
        addu(HI, *HI + c, hi * (y & 1));
        y >>= 1;
    }
}

void divu(word * r,  word * q, word x, word y)
{
    *q = 0;
    *r = x;
    word sum = y;
    
    while (x > sum)
    {
        sum <<= 1;
    }
    while (sum >= y)
    {
        word mult;
        if (sum <= *r)
        {
            mult = 1;
        }
        else
            mult = 0;
        
        *q = (*q << 1) ^ mult;
        *r -= sum * mult;
        sum >>=1;
        
    }
}
