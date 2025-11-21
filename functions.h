#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <cmath>
#include <list>
#include <fstream>
#include <stdexcept>

const int MAX_TEXTSEGMENT_SIZE = 268435456 - 67108864;
const int TS_ADDRESS = 67108864;
const int MAX_BUF = 1024;
// const int max_int = 18446744073709551616;

static std::map< std::string, int32_t > REGISTER_NOMENCLATURE = {
    {"$r0", 0}, {"$at", 1}, {"$v0", 2},  {"$v1", 3},  {"$a0", 4},  {"$a1", 5},  {"$a2", 6},  {"$a3", 7},
    {"$t0", 8}, {"$t1", 9}, {"$t2", 10}, {"$t3", 11}, {"$t4", 12}, {"$t5", 13}, {"$t6", 14}, {"$t7", 15},
    {"$s0", 16}, {"$s1", 17}, {"$s2", 18}, {"$s3", 19}, {"$s4", 20}, {"$s5", 21}, {"$s6", 22}, {"$s7", 23},
    {"$t8", 24}, {"$t9", 25}, {"$k0", 26}, {"$k1", 27}, {"$gp", 28}, {"$sp", 29}, {"$fp", 30}, {"$ra", 31}
};


//=========================================================================================================
// pseudoinstruction should map to a list of instructions with constants and variables
// li -> [[ori $%s, $0, %d]]
// lw -> [[lui $1, %s], [lw $%s, 12($1)]]
// la -> [[lui $1, %s], [ori $%s, $1, 16]]
// blt ->[[slt $1, $%s, $%s], [bne $1, $0, %s]]
// ble ->[[slt $1, $%s, $%s], [beq $1, $0, %s]]
// bgt ->[[slt $1, $%s, $%s], [bne $1, $0, %s]]
//=========================================================================================================
static std::map<std::string, std::list< std::vector<std::string> > > PSEUDO_INSTRUCTIONS = {
    {
        "li",
        {
            {"ori", "1", "$0", "2"} // This is one vector<string>
        }
    },
    {
        "la",
        {
            {"lui", "$1", "2"},
            {"ori", "1", "$1", "16"}
        }
    }
};

static std::map< std::string, int32_t > OPERATIONS = {
    {"lui", (7 << 6)}, {"ori", (13 << 6)}, {"add", 32},
    {"addi", 512}, {"addu", 576}, {"div", 26}, {"divu", 27},
    {"mfhi", 16}, {"mflo", 18}, {"lw", 35}, {"beq", 256}
};

void append_to_path(char * path, int & size, const char * file="");
void print_bin(int x, int len);
int get_numeric(const std::string & s);
void instruction_lexer(const std::string & s, std::vector< std::string > & token,
                       std::string & Label);

int32_t len(const char * s);
bool strcmp(const std::string & s, const std::string & c);
template< typename T >
std::ostream & operator<<(std::ostream & cout, const std::vector<T> & v)
{
    std::string delim = "";
    std::cout << '[';
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << delim << '[' << v[i] << ']';
        delim = ", ";
        
    }
    std::cout << ']';
    return cout;
}

int get_register(const std::string & s);

    
//const char ** addressable_reg[32] = {"r0","at","v0",""}

/* unsigned char * uint_to_hexad(int32_t i); */
/* unsigned char * uint_to_buff(int32_t i); */
/* int32_t hexad_to_uint(unsigned char buff[]); */
/* int32_t buff_to_int(unsigned char buff[]); */

#endif
