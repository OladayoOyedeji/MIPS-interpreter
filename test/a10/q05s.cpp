// file: q05s.cpp
#include <iostream>
#include <string>

typedef uint32_t bit; // only least significant bit of uint32_t should be used
typedef uint32_t word;

void readbits(word * x);
void printbit(bit x);
void printbits(word x);
void bit_half_adder(bit * s, bit * c, bit x, bit y);   // 1-bit half adder
void bit_full_adder(bit * s, bit * c1, bit x, bit y, bit c0);   // 1-bit full adder
void addu (word * ret, word x, word y);           // 32-bit unsigned int addition
void comp (word * ret, word x);                   // 32-bit two's complement
void subu (word * ret, word x, word y);           // 32-bit unsigned int subtraction
void multu(word * HI, word * LO, word x, word y); // 32-bit unsigned int mult w
word divu (word * r,  word * q, word x, word y);  // 32-bit unsigned int div


bit  error = 0;                                  // error: set to 1 if overflow,
                                                 //        otherwise set to 0
void add (word * ret, word x, word y);           // 32-bit signed int addition
void sub (word * ret, word x, word y);           // 32-bit signed int subtraction
void mult(word * HI, word * LO, word x, word y); // 32-bit signed int mult w
word div (word * r,  word * q, word x, word y);  // 32-bit signed int div

void readbits(word * x)
{
    std::string s;
    std::cin >> s;
    auto p = s.begin();
    for (int i = 31; i >= 0; --i)
    {
        int b = (*p++ == '0' ? 0 : 1);
        *x |= (b << i);
    }
}

void readbit(word * x)
{
    std::string s;
    std::cin >> s;
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

void addu (word * ret, word x, word y)
{
}

void calculator()
{
    // USAGE:
    // 1. User enters "123+456" or "123-456" or "-123--456" or "-123*-456".
    //    Note: no spaces. All integers are treated as signed 32-bit integers.
    // 2. Calculator prints the result. Display is right justify in the array
    //    of 7 segment display. If error bit is 1, print "Error" in the array
    //    of 7 segment display. Print the result as signed 32-bit integer.
    //    In particular, for mult, print LO. For div, print q (the quotient). 
}
    
int main()
{
    bit s = 0, c = 0, a = 0, b = 0;
    word w = 0, x = 0, y = 0, z = 0;

    int option;
    std::cin >> option;
    switch (option)
    {
        case 0: // test readbits and printbits
            readbits(&w);
            printbits(w);
            break;
        case 1: // test readbit and printbit
            readbit(&w);
            printbit(w);
            break;
        /*
        case 2: // test addu
            readbits(&x);
            readbits(&y);
            addu(&w, x, y);
            printbits(w);
            break;
        case 3: // test comp
            readbits(&x);
            comp(&w, x);
            printbits(w);
            break;
        case 4: // test subu
        case 5: // test multu (print HI and then LO)
        case 6: // test divu (print r and then q)
        
        case 7: // test add
        case 8: // test sub
        case 9: // test mult
        case 10: // test div

        case 11:
            calculator();
            break;
        */
    }
    
    return 0;
}
