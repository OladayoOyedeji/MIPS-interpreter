#include "Machine_Format.h"
#include "Arithmetic_operations.h"

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

void MachineFormat::execute_code(RegisterFile & r, uint32_t & PC, unsigned char * memory)
{
    std::cout << PC << std::endl;
    switch (operation_)
    {
        // case JR:
        case 9:
            PC = r[rs_];
            PC += 4;
            // machine code 0 <-> r[rs_] <-> 0 <-> 0 <-> 0 <-> func
            break;
            
        // case SYSCALL
        case 12:
            //SignalException(r[2], r[4]);
            PC += 4;
            break;
            
        // case MFHI:
        case 16:
            r[rd_] = r.HI();
            PC += 4;
            break;
            
        // case MFLO:
        case 18:
            r[rd_] = r.LO();
            PC += 4;
            break;

        // case MULT:
        case 24:
            break;

        // case MULTU:
        case 25:
            multu(&r.HI(), &r.LO(), r[rs_], r[rt_]);
            PC += 4;
            break;
            
        // case DIV:
        case 26:
            break;
            
        // case DIVU:
        case 27:
            divu(&r.HI(), &r.LO(), r[rs_], r[rt_]);
            break;
            
        // case ADD:
        case 32:
            // std::cout << r[rs_] << ' ' << r[rt_] << std::endl;
            r[rd_] = r[rs_] + r[rt_];
            PC += 4;
            break;

        // case ADDU:
        case 33:
            addu(&r[rd_], r[rs_], r[rt_]);
            PC += 4;
            break;
        // case SUB:
        case 34:
            break;
            
        // case SUBU:
        case 35:
            subu(&r[rd_], r[rs_], r[rt_]);
            PC += 4;
            break;

        // case AND:
        case 36:
            r[rd_] = r[rs_] & r[rt_];
            PC += 4;
            break;

        // case SLT:
        case 42:
            r[rd_] = r[rs_] < r[rt_];
            PC += 4;
            break;
            
        // case BLTZ:
        case 64:
            PC = (r[rs_] < 0 ? PC = imm_: PC + 4);
            break;

        // case J:
        case 128:
            PC = imm_;
            break;
            
        // case JAL:
        case 192:
            r[31] = PC;
            PC = imm_;
            break;
            
        // case BEQ:
        case 256:
            PC = (r[rs_] == r[rt_] ? PC = imm_: PC + 4);
            break;

        // case BNE:
        case 320:
            PC = (r[rs_] != 0 ? PC = imm_: PC + 4);
            break;
            
        // case BLEZ:
        case 384:
            PC = (r[rs_] <= 0 ? PC = imm_: PC + 4);
            break;

        // case ADDI:
        case 512:
            
            break;
        // case ORI:
        case 832:
            r[rt_] = r[rs_] | imm_;
            PC += 4;
            break;

        // case MUL:
        case 898:
            break;

        // case LW:
        // case 2240:
        //     unsigned char * p = (unsigned char *) &(r[rt_]);
        //     int i = imm_ - DS_ADDRESS;
        //     *p = memory[i];
        //     *(p+1) = memory[i+1];
        //     *(p+2) = memory[i+2];
        //     *(p+3) = memory[i+3];
        //     break;
            
        // case SW:
        case 2752:
        {
            unsigned char * p = (unsigned char *) &(r[rt_]);
            int i = imm_ - DS_ADDRESS;
            memory[i] = *p;
            memory[i+1] = *(p+1);
            memory[i+2] = *(p+2);
            memory[i+3] = *(p+3);
            break;
        }   
        default:
            PC += 4;
    }
}
