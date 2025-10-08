// File   : Register_File.h
// Author : Robert

#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

class RegisterFile
{
public:
    RegisterFile()
    {}
    int32_t & get_register(const char * s);
    int32_t & get_register(const char * s) const;
    int32_t operator[](int i) const;
    int32_t & operator[](int i);
private:
    int32_t x_[32];
    int32_t HI_;
    int32_t LO_;
    int32_t PC_;
};

#endif
