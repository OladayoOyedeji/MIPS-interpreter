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
    MachineFormat(int16_t v[])
        : operation_(v[0]), rs_(v[1]), rt_(v[2]),
          rd_(v[3]), imm_(v[4]), shamt_(v[5])
    {}
    void execute_code(RegisterFile & r);
    int16_t imm() const
    {
        return imm_;
    }
    int16_t & imm()
    {
        return imm_;
    }
private:
    int16_t operation_;
    int16_t rs_;
    int16_t rt_;
    int16_t rd_;
    int16_t imm_;
    int16_t shamt_;

    std::string instruction_;
};



#endif
