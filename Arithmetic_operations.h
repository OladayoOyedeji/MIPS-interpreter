#ifndef ARITHMETIC_OPERATIONS_H
#define ARITHMETIC_OPERATIONS_H

#include "functions.h"

typedef uint32_t bit; // only least significant bit of uint32_t should be used
typedef uint32_t word;

void readbits(word * x);
void printbit(word x);
void printbits(word x);
void bit_adder(word * s, word * c, word x, word y);   // 1-bit full adder
bit addu(word * ret, word x, word y);           // 32-bit unsigned int addition
void comp(word * ret, word x);                   // 32-bit two's complement
void subu(word * ret, word x, word y);           // 32-bit unsigned int subtraction
void multu(word * HI, word * LO, word x, word y); // 32-bit unsigned int mult w
void divu(word * r,  word * q, word x, word y);  // 32-bit unsigned int div

/* bit add(word * ret, word x, word y);           // 32-bit signed int addition */
/* void sub(word * ret, word x, word y);           // 32-bit signed int subtraction */
/* void mult(word * HI, word * LO, word x, word y); // 32-bit signed int mult w */
void div(word * r,  word * q, word x, word y);  // 32-bit signed int div

#endif
