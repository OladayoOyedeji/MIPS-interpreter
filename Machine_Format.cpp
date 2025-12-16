#include "Machine_Format.h"

void get_operation(const std::string & s, int32_t & operation,
                   int32_t & type)
{
    if (s == "lui")
    {
        operation = (7 << 5);
        type = 1;
        return;
    }
    if (s == "ori")
    {
        operation = (48 << 5);
        type = 1;
        return;
    }
}


MachineFormat::MachineFormat(const std::vector< std::string > & v)
{
    // get the operation first
    if (OPERATIONS.find(v[0]) != OPERATIONS.end())
    {
        operation_ = OPERATIONS[v[0]];
    }
    else
    {
        throw std::runtime_error("Operation not found");
    }
    // std::cout << operation_ << std::endl;
    int opcode = operation_ >> 6;
    int funct = operation_ & ((1 << 6) - 1);

    // print_bin(opcode, 6);
    // std::cout << ' ' ;
    // print_bin(funct, 6);
    // std::cout << std::endl;

    switch (opcode)
    {
        // opcode 0 means it in R format
        case 0: 
            rd_ = get_register(v[1]);

            //std::cout << v.size() << std::endl;
            // 3 register operation
            if (v.size() == 4)
            {
                rs_ = get_register(v[2]);
                rt_ = get_register(v[3]);
            }
            else
            {
                // shift
                rt_ = get_register(v[2]);
                shamt_ = get_numeric(v[3]);
            }
            // opcode 2 or 3 mean its in j format
            break;
        case 2:
        case 3:
            imm_ = get_numeric(v[1]);
            break;

            // others mean I format
        default:
            // std::cout << v[1] << ' ' << v[2] << std::endl;

            rt_ = get_register(v[1]);
            
            rs_ = get_register(v[2]);

            imm_ = get_numeric(v[3]);
 
            // std::cout << v[0] << " $" << rt_ << ", $" << rs_ << ", " << imm_ << std::endl;
    }
}

int MachineFormat::convert_to_machine()
{
    int opcode = operation_ >> 6;
    int funct = operation_ & ((1 << 6) - 1);
    int code = opcode;
    switch(opcode)
    {
        case 0:
            (code <<= 5) | rs_;
            (code <<= 5) | rt_;
            (code <<= 5) | rd_;
            (code <<= 5) | shamt_;
            (code <<= 6) | funct;
            break;
        case 2:
        case 3:
            break;
        default:
            (code <<= 5) | rs_;
            (code <<= 5) | rt_;
            (code <<= 5) | imm_;
    }
    return code;
}

int32_t MachineFormat::imm() const
{
    return imm_;
}
int32_t & MachineFormat::imm()
{
    return imm_;
}
void MachineFormat::insert_imm(int32_t imm)
{
    if (imm_mode == 1)
    {
        imm_ = imm >> 16;
    }
    else if (imm_mode == 2)
    {
        imm_ = imm & ((1 << 16) - 1);
    }
    else
        imm_ = imm;
}
    
int32_t MachineFormat::operation() const
{
    return operation_;
}
    
int32_t & MachineFormat::operation()
{
    return operation_;
}
    
int32_t MachineFormat::rs() const
{
    return rs_;
}
    
int32_t & MachineFormat::rs()
{
    return rs_;
}
    
int32_t MachineFormat::rt() const
{
    return rt_;
}
    
int32_t & MachineFormat::rt()
{
    return rt_;
}
    
int32_t MachineFormat::rd() const
{
    return rd_;
}

int32_t & MachineFormat::rd()
{
    return rd_;
}
    
int32_t MachineFormat::shamt() const
{
    return shamt_;
}

int32_t & MachineFormat::shamt()
{
    return shamt_;
}


const std::string & MachineFormat::return_code()
{
    std::string code;
    switch (operation())
    {
        // case JR: jr rs
        case 9:
            code = "jr\t" + std::to_string(rs_);
            break;
            
        // case SYSCALL: syscall
        case 12:
            code = "syscall";
            break;
            
        // case MFHI: mfhi HI, rd
        case 16:
            code = "mfhi\t $" + std::to_string(rd_);
            break;
            
        // case MTHI: mthi HI, rd
        case 17:
            code = "mthi\t $" + std::to_string(rd_);
            break;
            
        // case MFLO: mflo LO, rd
        case 18:
            code = "mflo\t $" + std::to_string(rd_);
            break;

        // case MTLO: mtlo LO, rd
        case 19:
            code = "mlfo\t $" + std::to_string(rd_);
            break;
            
        // case MULT: mult rs, rt
        case 24:
            code =  "mult\t $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;
            
        // case MULTU: multu rs, rt
        case 25:
            code =  "multu\t $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;
            
        // case DIV: div rs, rt
        case 26:
            code =  "div\t $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;
            
        // case DIVU: divu rs, rt
        case 27:
            code =  "divu\t $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;
            
        // case ADD: add rd, rs, rt
        case 32:
            code =  "add\t $" + std::to_string(rd_) + ", $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;

        // case ADDU: addu rd, rs, rt
        case 33:
            code =  "addu\t $" + std::to_string(rd_) + ", $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;
            
        // case SUB:
        case 34:
            code = "sub\t $" + std::to_string(rd_) + ", $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;
            
        // case SUBU:
        case 35:
            code = "subu\t $" + std::to_string(rd_) + ", $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;

        // case AND:
        case 36:
            code = "and\t $" + std::to_string(rd_) + ", $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;

        // case XOR:
        case 38:
            code = "xor\t $" + std::to_string(rd_) + ", $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            
            break;
            
        // case SLT:
        case 42:
            code = "slt\t $" + std::to_string(rd_) + ", $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;
            
        // case BLTZ:
        case 64:
            code = "bltz\t $" + std::to_string(rs_) + ", " + std::to_string(imm_);
            break;

        // case J:
        case 128:
            code = "j\t" + std::to_string(uint32_t(imm_));
            break;
            
        // case JAL:
        case 192:
            code = "jal\t" + std::to_string(uint32_t(imm_));
            break;
            
        // case BEQ:
        case 256:
            code = "beq\t $" + std::to_string(rs_) + ", $" + std::to_string(rt_) + ", " + std::to_string(uint32_t(imm_));
            break;

        // case BNE:
        case 320:
            code = "bne\t $" + std::to_string(rs_) + ", $" + std::to_string(rt_) + ", " + std::to_string(uint32_t(imm_));
            break;
            
        // case BLEZ:
        case 384:
            code = "blez\t $" + std::to_string(rs_) + ", " + std::to_string(uint32_t(imm_));
            break;

        // case ADDI:
        case 512:
            code = "addi\t $" + std::to_string(rt_) + ", $" + std::to_string(rs_) + ", " + std::to_string(imm_);
            break;

        // case ADDIU:
        case 576:
            code = "addiu\t $" + std::to_string(rt_) + ", $" + std::to_string(rs_) + ", " + std::to_string(imm_);
            break;

        // case SLTIU:
        case 704:
            code = "sltiu\t $" + std::to_string(rt_) + ", $" + std::to_string(rs_) + ", " + std::to_string(imm_);
            break;
        // case ORI:
        case 832:
            code = "ori\t $" + std::to_string(rt_) + ", $" + std::to_string(rs_) + ", " + std::to_string(imm_);
            break;

        // case LUI:
        case 960:
            code = "lui\t $" + std::to_string(rt_) + ", " + std::to_string(imm_);
            break;
            
        // case MUL:
        case 1794:
            code = "mul\t $" + std::to_string(rd_) + ", $" + std::to_string(rs_) + ", $" + std::to_string(rt_);
            break;

        // case LB:
        case 2048:
            code = "lb\t $" + std::to_string(rt_) + ", " + std::to_string(imm_) + "($" + std::to_string(rs_) + ")";
            break;
       
        // case LW:
        case 2240:
            code = "lw\t $" + std::to_string(rt_) + ", " + std::to_string(imm_) + "($" + std::to_string(rs_) + ")";
            break;

        // case SB:
        case 2560:
            code = "sb\t $" + std::to_string(rt_) + ", " + std::to_string(imm_) + "($" + std::to_string(rs_) + ")";
            break;
        
        // case SW:
        case 2752:
            code = "sw\t $" + std::to_string(rt_) + ", " + std::to_string(imm_) + "($" + std::to_string(rs_) + ")";
            break;
        default:
            code = "instruction doesnt exist: " + std::to_string(operation_);
    }
    code_ = code;
    return code_;
}
