// File   : Register_File.h
// Author : Robert

#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

class RegisterFile
{
public:
    RegisterFile()
    {}
    int32_t operator[](int i) const;
    int32_t & operator[](int i);
private:
    int32_t x_[32];
};

#endif
