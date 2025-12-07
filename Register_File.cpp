#include "Register_File.h"

reg_int32::reg_int32(uint32_t x_, bool print_signed)
    : x(x_), print_signed_(print_signed)
{}

reg_int32::reg_int32(int x_)
    : x(x_), print_signed_(true)
{}

reg_int32 & reg_int32::operator=(reg_int32 i)
{
    x = i.x;
    print_signed_ = i.print_signed_;
    return *this;
}
    
reg_int32 & reg_int32::operator=(int32_t i)
{
    x = i;
    return *this;
}

bool reg_int32::operator==(reg_int32 i)
{
    int64_t x_ = (  print_signed_ ? int32_t(  x) :   x);
    int64_t y_ = (i.print_signed_ ? int32_t(i.x) : i.x);
    return (x_ == y_);
}

bool reg_int32::operator==(int i)
{
    return (*this == reg_int32(i));
}

bool reg_int32::operator!=(reg_int32 i)
{
    int64_t x_ = (  print_signed_ ? int32_t(  x) :   x);
    int64_t y_ = (i.print_signed_ ? int32_t(i.x) : i.x);
    return (x_ != y_);
}

bool reg_int32::operator!=(int i)
{
    return (*this != reg_int32(i));
}
    
bool reg_int32::operator<(reg_int32 i)
{
    int64_t x_ = (  print_signed_ ? int32_t(  x) :   x);
    int64_t y_ = (i.print_signed_ ? int32_t(i.x) : i.x);
    return (x_ < y_);
}

bool reg_int32::operator<(int i)
{
    return (*this < reg_int32(i));
}
    
bool reg_int32::operator<=(reg_int32 i)
{
    return (*this < i || *this == i);
}

bool reg_int32::operator<=(int i)
{
    return (*this <= reg_int32(i));
}
    
bool reg_int32::operator>(reg_int32 i)
{
    int64_t x_ = (  print_signed_ ? int32_t(  x) :   x);
    int64_t y_ = (i.print_signed_ ? int32_t(i.x) : i.x);
    return (x_ > y_);
}

bool reg_int32::operator>(int i)
{
    return (*this > reg_int32(i));
}
    
bool reg_int32::operator>=(reg_int32 i)
{
    return (*this > i || *this == i);
}

bool reg_int32::operator>=(int i)
{
    return (*this >= reg_int32(i));
}

void RegisterFile::display_reg() const
{
    std::cout << std::dec << "==========================================================\n"
              << "Registers\n"
              << "==========================================================\n";
    
    
    std::cout << "$r0| " << std::right << std::setw(10) << std::setfill('0') << x_[0].x << " "
              << "$at| " << std::right << std::setw(10) << std::setfill('0') << x_[1].x << " "
              << "$v0| " << std::right << std::setw(10) << std::setfill('0') << x_[2].x << " "
              << "$v1| " << std::right << std::setw(10) << std::setfill('0') << x_[3].x << "\n"
              << "$a0| " << std::right << std::setw(10) << std::setfill('0') << x_[4].x << " "
              << "$a1| " << std::right << std::setw(10) << std::setfill('0') << x_[5].x << " "
              << "$a2| " << std::right << std::setw(10) << std::setfill('0') << x_[6].x << " "
              << "$a3| " << std::right << std::setw(10) << std::setfill('0') << x_[7].x << "\n"
              << "$t0| " << std::right << std::setw(10) << std::setfill('0') << x_[8].x << " "
              << "$t1| " << std::right << std::setw(10) << std::setfill('0') << x_[9].x << " "
              << "$t2| " << std::right << std::setw(10) << std::setfill('0') << x_[10].x << " "
              << "$t3| " << std::right << std::setw(10) << std::setfill('0') << x_[11].x << "\n"
              << "$t4| " << std::right << std::setw(10) << std::setfill('0') << x_[12].x << " "
              << "$t5| " << std::right << std::setw(10) << std::setfill('0') << x_[13].x << " "
              << "$t6| " << std::right << std::setw(10) << std::setfill('0') << x_[14].x << " "
              << "$t7| " << std::right << std::setw(10) << std::setfill('0') << x_[15].x << "\n"
              << "$s0| " << std::right << std::setw(10) << std::setfill('0') << x_[16].x << " "
              << "$s1| " << std::right << std::setw(10) << std::setfill('0') << x_[17].x << " "
              << "$s2| " << std::right << std::setw(10) << std::setfill('0') << x_[18].x << " "
              << "$s3| " << std::right << std::setw(10) << std::setfill('0') << x_[19].x << "\n"
              << "$s4| " << std::right << std::setw(10) << std::setfill('0') << x_[20].x << " "
              << "$s5| " << std::right << std::setw(10) << std::setfill('0') << x_[21].x << " "
              << "$s6| " << std::right << std::setw(10) << std::setfill('0') << x_[22].x << " "
              << "$s7| " << std::right << std::setw(10) << std::setfill('0') << x_[23].x << "\n"
              << "$t8| " << std::right << std::setw(10) << std::setfill('0') << x_[24].x << " "
              << "$t9| " << std::right << std::setw(10) << std::setfill('0') << x_[25].x << " "
              << "$k0| " << std::right << std::setw(10) << std::setfill('0') << x_[26].x << " "
              << "$k1| " << std::right << std::setw(10) << std::setfill('0') << x_[27].x << "\n"
              << "$gp| " << std::right << std::setw(10) << std::setfill('0') << x_[28].x << " "
              << "$sp| " << std::right << std::setw(10) << std::setfill('0') << x_[29].x << " "
              << "$fp| " << std::right << std::setw(10) << std::setfill('0') << x_[30].x << " "
              << "$ra| " << std::right << std::setw(10) << std::setfill('0') << x_[31].x
              << std::setfill(' ') << "\n";
}
reg_int32 RegisterFile::operator[](int i) const
{
    return x_[i];
}
    
reg_int32 & RegisterFile::operator[](int i)
{
    return x_[i];
}
    
reg_int32 RegisterFile::HI()const
{
    return HI_;
}
    
reg_int32 & RegisterFile::HI()
{
    return HI_;
}
    
reg_int32 RegisterFile::LO()const
{
    return LO_;
}

reg_int32 & RegisterFile::LO()
{
    return LO_;
}

std::ostream & operator<<(std::ostream & cout, reg_int32 i)
{
    if (i.print_signed_)
    {
        std::cout << int32_t(i.x);
    }
    else
        std::cout << i.x;
    return cout;
}
