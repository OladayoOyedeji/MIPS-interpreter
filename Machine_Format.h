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
    int convert_to_machine();
    int32_t imm() const;
    int32_t & imm();
    void insert_imm(int32_t imm);
    int32_t operation() const;
    int32_t & operation();
    int32_t rs() const;
    int32_t & rs();
    int32_t rt() const;
    int32_t & rt();
    int32_t rd() const;
    int32_t & rd();
    int32_t shamt() const;
    int32_t & shamt();
    const std::string & return_code();
private:
    int32_t operation_;
    int32_t rs_;
    int32_t rt_;
    int32_t rd_;
    int32_t imm_;
    int32_t shamt_;

    // 0:as it is, 1:upper 16 bit, 2:lower 16 bit
    int imm_mode;
    std::string code_;
};

#endif
