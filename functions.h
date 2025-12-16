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
#include <cstdint>
#include <cctype>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <format>
#include "Arithmetic_operations.h"

#include <filesystem>
#include <stdlib.h>

#ifdef _WIN32
#include <direct.h> // For _getcwd on Windows
#define GET_CURRENT_DIR _getcwd
#else
#include <unistd.h> // For getcwd on POSIX systems
#define GET_CURRENT_DIR getcwd
#endif


const int MAX_TEXTSEGMENT_SIZE = 268435456 - 67108864;
const int TS_ADDRESS = 67108864;
const int DS_ADDRESS = 268435456;
const int S_ADDRESS = 2147483648;
const int MAX_BUF = 1024;

class FileError
{
public:
    FileError()
        : errno_(errno)
    {}
    int errno_;
};

class OpenError: public FileError
{};
class ReadError: public FileError
{};
class WriteError: public FileError
{};

// const int max_int = 18446744073709551616;
class File
{
public:
    File(const std::string & filename)
    {
        fd_ = open(filename.c_str(), O_RDWR | O_CREAT, 0600);
        if (fd_ < 0) throw OpenError();
    }
    File(const char * filename)
    {
        fd_ = open(filename, O_RDWR | O_CREAT, 0600);
        if (fd_ < 0) throw OpenError();
    }
    ssize_t myread(unsigned char buff[], ssize_t size);
    ssize_t mywrite(unsigned char buff[], ssize_t size);
    off_t mylseek(off_t offset, int whence=SEEK_SET);
    void myclose()
    {
        close(fd_);
    }
    int fd_;
};

// std::ostream & operator<<(std::ostream & cout, FileError & e)
// {
//     cout << "Error " << e.errno_ << ": " << stderr(e.errno_);
//     cout.flush();
//     return cout;
// }

static std::map< std::string, int32_t > REGISTER_NOMENCLATURE = {
    {"$r0", 0}, {"$at", 1}, {"$v0", 2},  {"$v1", 3},  {"$a0", 4},  {"$a1", 5},  {"$a2", 6},  {"$a3", 7},
    {"$t0", 8}, {"$t1", 9}, {"$t2", 10}, {"$t3", 11}, {"$t4", 12}, {"$t5", 13}, {"$t6", 14}, {"$t7", 15},
    {"$s0", 16}, {"$s1", 17}, {"$s2", 18}, {"$s3", 19}, {"$s4", 20}, {"$s5", 21}, {"$s6", 22}, {"$s7", 23},
    {"$t8", 24}, {"$t9", 25}, {"$k0", 26}, {"$k1", 27}, {"$gp", 28}, {"$sp", 29}, {"$fp", 30}, {"$ra", 31}
};

// 0:operation_, 1:rs_, 2:rt_, 3:rd_, 4:imm_, 5:shamt_
enum {OPFUNCT, RS, RT, RD, IMM, SHAMT};

//=========================================================================================================
// pseudoinstruction should map to a list of instructions with constants and variables
// li -> [[ori $%s, $0, %d]]
// lw -> [[lui $1, %s], [lw $%s, 12($1)]]
// la -> [[lui $1, %s], [ori $%s, $1, 16]]
// blt ->[[slt $1, $%s, $%s], [bne $1, $0, %s]]
// ble ->[[slt $1, $%s, $%s], [beq $1, $0, %s]]
// bgt ->[[slt $1, $%s, $%s], [bne $1, $0, %s]]
//=========================================================================================================
static std::set<std::string > PSEUDO_INSTRUCTIONS = {"li","la","blt", "ble", "bgt", "bge", "move", "beqz", "bnez", "seq"};

static std::map< std::string, int32_t > OPERATIONS = {
    {"add", 32}, {"addi", 512}, {"addiu", 576}, {"addu", 33},
    {"and", 36}, {"andi", 768}, {"aui", 960}, 
    {"beq", 256}, {"bgtz", 448}, {"blez", 384}, {"bltz", 64}, {"bne", 320},
    {"div", 26}, {"divu", 27},
    {"j", 128}, {"jal", 192}, {"jr", 9}, 
    {"lb", 2048}, {"lui", 960}, {"lw", 2240},
    {"mfhi", 16}, {"mflo", 18}, {"mul", 1794}, {"mult", 24}, {"multu", 25},
    {"ori", (13 << 6)},
    {"sb", 2560}, {"slt", 42}, {"sltiu", 704}, {"sub", 34}, {"subu", 35}, {"sw", 2752}, {"syscall", 12},
    {"xor", 38}
};

void append_to_path(char * path, int & size, const char * file);
void append_to_path(std::string & path, const char * file="");
void print_bin(int x, int len);
int get_numeric(const std::string & s);
void get_imm_reg(const std::string & s, std::vector< std::string > & token);
void instruction_lexer(const std::string & s, std::vector< std::string > & token,
                       std::string & Label);
void data_lexer(const std::string & s, std::vector<std::string> & token,
                std::string & Label);

int32_t len(const char * s);
bool strcmp(const std::string & s, const std::string & c);
void print_unsigned_char(unsigned char c);
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


#endif
