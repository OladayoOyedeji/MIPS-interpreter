// File   : Register_File.h
// Author : Robert

#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

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
    unsigned int & get_register(const char * s);
    unsigned int & get_register(const char * s) const;
    unsigned int operator[](int i) const
    {
        return x_[i];
    }
    unsigned int & operator[](int i)
    {
        return x_[i];
    }
private:
    unsigned int x_[32];
    int32_t HI_;
    int32_t LO_;
    int32_t PC_;
};

#endif
