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
    void execute_code(RegisterFile & r);
private:
    int32_t operation_;
    int32_t rs_;
    int32_t rt_;
    int32_t rd_;
    int16_t imm_;
    int32_t shamt_;

    std::string instruction_;
};



#endif
