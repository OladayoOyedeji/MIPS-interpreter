// File   : Register_File.h
// Author : Robert

#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include "functions.h"
#include <cstdint>

class RegisterFile
{
public:
    RegisterFile()
    {
        for (int i = 0; i < 32; ++i)
        {
            x_[i] = 0;
        }
    }
    uint32_t & get_register(const char * s);
    uint32_t & get_register(const char * s) const;
    uint32_t operator[](int i) const
    {
        return x_[i];
    }
    uint32_t & operator[](int i)
    {
        return x_[i];
    }
    uint32_t HI()const
    {
        return HI_;
    }
    uint32_t LO()const
    {
        return LO_;
    }
private:
    uint32_t x_[32];
    uint32_t HI_;
    uint32_t LO_;
    
};

#endif
