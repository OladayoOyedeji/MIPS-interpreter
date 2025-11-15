#ifndef TEXTSEGMENT_H
#define TEXTSEGMENT_H

#include "functions.h"
#include "Machine_Format.h"
#include <exception>

class SizeError: public std::exception
{};


void instruction_lexer(const std::string & s, std::vector< std::string > & token);

class TextSegment
{
public:
    TextSegment()
        : size_(0),
          starting_address_(TS_ADDRESS)
    {}
    void print_addressh(int i) const
    {
        if (i > size_)
        {
            throw SizeError();
        }
        std::cout << "0x" << std::setw(8) << std::setfill('0')
                  << std::right << std::hex << (starting_address_ + i * 4);
    } 
    void insert(const std::string & s)
    {
        if (size_ == MAX_TEXTSEGMENT_SIZE) throw SizeError();
        std::vector< std::string > token;

        instruction_lexer(s, token);
        std::cout << token <<std::endl;

        //===============================================================
        // check if the operation is a pseudo instruction
        //===============================================================
        size_++;
    }
    void run_command();
private:
    std::vector< MachineFormat > machine_format_;
    int size_;
    int32_t starting_address_;
};

#endif
