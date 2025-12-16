// File   : Register_File.h
// Author : Robert

#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include "functions.h"
#include <cstdint>

class reg_int32
{
public:
    reg_int32(uint32_t x_=0, bool print_signed=false);
    reg_int32(int x_);
    reg_int32 & operator=(reg_int32 i);
    reg_int32 & operator=(int32_t i);
    reg_int32 & operator=(uint32_t i);
    bool operator==(reg_int32 i);
    bool operator==(int i);
    bool operator!=(reg_int32 i);
    bool operator!=(int i);
    bool operator<(reg_int32 i);
    bool operator<(int i);
    bool operator<=(reg_int32 i);
    bool operator<=(int i);
    bool operator>(reg_int32 i);
    bool operator>(int i);
    bool operator>=(reg_int32 i);
    bool operator>=(int i);
    operator uint32_t()
    {
        return x;
    }
    uint32_t x;
    bool print_signed_;
};

std::ostream & operator<<(std::ostream & cout, reg_int32 i);
    
class RegisterFile
{
public:
    RegisterFile()
    {
        x_[29] = S_ADDRESS;
    }
    void display_reg() const;
    reg_int32 operator[](int i) const;
    reg_int32 & operator[](int i);
    reg_int32 HI()const;
    reg_int32 & HI();
    reg_int32 LO()const;
    reg_int32 & LO();
    
private:
    reg_int32 x_[32];
    reg_int32 HI_;
    reg_int32 LO_;
    
};

#endif
