#ifndef TEXTSEGMENT_H
#define TEXTSEGMENT_H

#include "functions.h"
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
    void print_addressh(int i) const
    {
        if (i > size_)
        {
            throw SizeError();
        }
        std::cout << "0x" << std::setw(8) << std::setfill('0')
                  << std::right << std::hex << (starting_address_ + i * 4);
    }
    void insert(const char * s)
    {
        if (size_ == MAX_TEXTSEGMENT_SIZE) throw SizeError();
        instructions_[size_++] = s;
    }
    void run_command();
private:
    std::map< int32_t, std::string > instructions_;
    int size_;
    int32_t starting_address_;
};

#endif
