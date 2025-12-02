#ifndef MACHINE_FORMAT_H
#define MACHINE_FORMAT_H

#include "functions.h"
#include "Register_File.h"


class MachineFormat
{
public:
    
// assuming we have removed the label on it
// and trailing zeros are gone
    MachineFormat(const std::vector< std::string > & v);
    MachineFormat(int32_t v[], int i=0)
        : operation_(v[0]), rs_(v[1]), rt_(v[2]),
          rd_(v[3]), imm_(v[4]), shamt_(v[5]), imm_mode(i)
    {}
    void execute_code(RegisterFile & r, uint32_t & PC, unsigned char * memory);
    int32_t imm() const
    {
        return imm_;
    }
    int32_t & imm()
    {
        return imm_;
    }
    void insert_imm(int32_t imm)
    {
        if (imm_mode == 1)
        {
            imm_ = imm >> 16;
        }
        else if (imm_mode == 2)
        {
            imm_ = imm & ((1 << 16) - 1);
        }
    }
private:
    int32_t operation_;
    int32_t rs_;
    int32_t rt_;
    int32_t rd_;
    int32_t imm_;
    int32_t shamt_;

    // 0:as it is, 1:upper 16 bit, 2:lower 16 bit
    int imm_mode;
    
    std::string instruction_;
};



#endif
