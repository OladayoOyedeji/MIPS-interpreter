#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <fstream>

const int MAX_TEXTSEGMENT_SIZE = 268435456 - 67108864;
const int TS_ADDRESS = 67108864;
const int MAX_BUF = 1024;

int32_t len(const char * s);
bool strcmp(const std::string & s, const std::string & c);
//const char ** addressable_reg[32] = {"r0","at","v0",""}

/* unsigned char * uint_to_hexad(int32_t i); */
/* unsigned char * uint_to_buff(int32_t i); */
/* int32_t hexad_to_uint(unsigned char buff[]); */
/* int32_t buff_to_int(unsigned char buff[]); */

#endif
