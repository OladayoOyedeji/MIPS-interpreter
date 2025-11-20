#ifndef TEXTSEGMENT_H
#define TEXTSEGMENT_H

#include "functions.h"
#include "Machine_Format.h"
#include <exception>

class SizeError: public std::exception
{};

class TextSegment
{
public:
    TextSegment()
        : size_(0),
          starting_address_(TS_ADDRESS)
    {}
    void print_addressh(int i) const;
    void insert(const std::vector< std::string > & token);
    void run_command();
// private:
    std::vector< MachineFormat * > machine_format_;
    int size_;
    int32_t starting_address_;
};

#endif
