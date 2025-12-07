#include "Memory.h"
#include <bitset>
// const int MAX_BUF = 1024;

void execute_code(MachineFormat & instruction, RegisterFile & r,
                  uint32_t & PC, Memory & memory)

{
    //std::cout << PC << std::endl;
    unsigned char * p;
    int i;
    // std::cout << "operation: ";
    // std::cout << operation() << std::endl;
    switch (instruction.operation())
    {
        // case JR:
        case 9:
            PC = r[instruction.rs()] + 4;
            // machine code 0 <-> r[instruction.rs()] <-> 0 <-> 0 <-> 0 <-> func
            break;
            
        // case SYSCALL
        case 12:
            //SignalException(r[2], r[4]);
            throw std::runtime_error("Signal Exception");
            break;
            
        // case MFHI:
        case 16:
            r[instruction.rd()] = r.HI();
            PC += 4;
            break;
            
        // case MTHI:
        case 17:
            r.HI() = r[instruction.rd()];
            PC += 4;
            break;
            
        // case MFLO:
        case 18:
            r[instruction.rd()] = r.LO();
            PC += 4;
            break;

        // case MTLO:
        case 19:
            r.LO() = r[instruction.rd()];
            PC += 4;
            break;
            
        // case MULT:
        case 24:
            multu(&r.HI().x, &r.LO().x, r[instruction.rs()].x, r[instruction.rt()].x);
            r.HI().print_signed_ = true; r.LO().print_signed_ = true;
            break;
            
        // case MULTU:
        case 25:
            multu(&r.HI().x, &r.LO().x, r[instruction.rs()].x, r[instruction.rt()].x);
            r.HI().print_signed_ = false; r.LO().print_signed_ = false;
            PC += 4;
            break;
            
        // case DIV:
        case 26:
            div(&(r.HI().x), &(r.LO().x), r[instruction.rs()].x, r[instruction.rt()].x);
            r.HI().print_signed_ = true; r.LO().print_signed_ = true;
            PC += 4;
            break;
            
        // case DIVU:
        case 27:
            divu(&(r.HI().x), &(r.LO().x), r[instruction.rs()].x, r[instruction.rt()].x);
            r.HI().print_signed_ = false; r.LO().print_signed_ = false;
            PC+=4;
            break;
            
        // case ADD:
        case 32:
            // std::cout << r[instruction.rs()] << ' ' << r[instruction.rt()] << std::endl;
            r[instruction.rd()] = reg_int32(r[instruction.rs()].x + r[instruction.rt()].x, true);
            PC += 4;
            break;

        // case ADDU:
        case 33:
            addu(&r[instruction.rd()].x, r[instruction.rs()].x, r[instruction.rt()].x);
            r[instruction.rd()].print_signed_ = false;
            PC += 4;
            break;
            
        // case SUB:
        case 34:
            subu(&r[instruction.rd()].x, r[instruction.rs()].x, r[instruction.rt()].x);
            r[instruction.rd()].print_signed_ = true;
            break;
            
        // case SUBU:
        case 35:
            subu(&r[instruction.rd()].x, r[instruction.rs()].x, r[instruction.rt()].x);
            r[instruction.rd()].print_signed_ = false;
            PC += 4;
            break;

        // case AND:
        case 36:
            r[instruction.rd()].x = r[instruction.rs()].x & r[instruction.rt()].x;
            PC += 4;
            break;

        // case XOR:
        case 38:
            r[instruction.rd()].x = r[instruction.rs()].x ^ r[instruction.rt()].x;
            PC+=4;
            break;
            
        // case SLT:
        case 42:
            r[instruction.rd()] = r[instruction.rs()] < r[instruction.rt()];
            PC += 4;
            break;
            
        // case BLTZ:
        case 64:
            std::cout << "reg: " << r[instruction.rs()] << std::endl;
            PC = (r[instruction.rs()] < 0 ? PC = instruction.imm(): PC + 4);
            break;

        // case J:
        case 128:
            PC = instruction.imm();
            break;
            
        // case JAL:
        case 192:
            r[31] = PC;
            PC = instruction.imm();
            break;
            
        // case BEQ:
        case 256:
            PC = (r[instruction.rs()] == r[instruction.rt()] ? PC = instruction.imm(): PC + 4);
            break;

        // case BNE:
        case 320:
            PC = (r[instruction.rs()] != r[instruction.rt()] ? PC = instruction.imm(): PC + 4);
            break;
            
        // case BLEZ:
        case 384:
            PC = (r[instruction.rs()] <= 0 ? PC = instruction.imm(): PC + 4);
            break;

        // case BGTZ:
        case 448:
            PC = (r[instruction.rs()] > 0 ? PC = instruction.imm(): PC + 4);
            break;
            
        // case ADDI:
        case 512:
            addu(&r[instruction.rt()].x, r[instruction.rs()].x, instruction.imm());
            r[instruction.rt()].print_signed_ = true;
            PC += 4;
            break;

        // case ADDIU:
        case 576:
            addu(&r[instruction.rt()].x, r[instruction.rs()].x, instruction.imm());
            r[instruction.rt()].print_signed_ = false;
            PC += 4;
            break;

        // case SLTIU:
        case 704:
            r[instruction.rt()] = reg_int32(r[instruction.rs()].x, false) < reg_int32(instruction.imm(), false);
            
            PC += 4;
            break;
        // case ORI:
        case 832:
            // std::cout << "ORI rs: " << std::bitset<32>(r[instruction.rs()])
            //           << " imm_ " << std::bitset<32>(instruction.imm()) << std::endl;
            r[instruction.rt()].x = r[instruction.rs()].x | instruction.imm();
            PC += 4;
            break;

        // case LUI:
        case 960:
            // std::cout << "LUI imm_ " << (instruction.imm() << 16) << std::endl;
            r[instruction.rt()].x = (instruction.imm() << 16);
            PC += 4;
            break;
            
        // case MUL:
        case 1794:
            r[instruction.rd()].x = r[instruction.rs()].x * r[instruction.rt()].x;
            r[instruction.rd()].print_signed_ = true;
            PC += 4;
            break;

        // case LB:
        case 2048:
        {
            uint32_t address = r[instruction.rs()].x + instruction.imm();
            // std::cout << "storing bytes" << std::endl;
            
            r[instruction.rt()].x = memory[address];
            PC += 4;
            // memory.read_bytes_from_memory(address, r[instruction.rt()].x);
            break;
        }
        // case LW:
        case 2240:
        {
            uint32_t address = r[instruction.rs()].x + instruction.imm();
            memory.read_bytes_from_memory(address, r[instruction.rt()].x);
            // p = (unsigned char *) &(r[rt_]);
            //i = r[instruction.rs()] - DS_ADDRESS + imm_;
            
            // *p = memory[i];
            // *(p+1) = memory[i+1];
            // *(p+2) = memory[i+2];
            // *(p+3) = memory[i+3];
            
            PC += 4;
            break;
        }

        // case SB:
        case 2560:
        {
            uint32_t address = r[instruction.rs()] + instruction.imm();
            unsigned char c = r[instruction.rt()];
            memory.write_a_byte_to_memory(address, c);
            PC += 4;
            break;
        }
        
        // case SW:
        case 2752:
        {
            uint32_t address = r[instruction.rs()].x + instruction.imm();
            memory.write_bytes_to_memory(address, r[instruction.rt()].x);
            // p = (unsigned char *) &(r[rt_]);
            // i = r[instruction.rs()] - DS_ADDRESS + imm_;
            // memory[i] = *p;
            // memory[i+1] = *(p+1);
            // memory[i+2] = *(p+2);
            // memory[i+3] = *(p+3);
            // if (i + 4 > size) size = i + 4;
            PC += 4;
            break;
        }
        default:
            PC += 4;
    }
}

Memory::~Memory()
{
    clear();
}
void Memory::print_instruction(uint32_t address)
{
    instruction_[address]->make_new_token();
}
void Memory::insert_imm(uint32_t key, uint32_t address)
{
    // std::cout << std::hex << address << std::endl;
    instruction_[key]->insert_imm(address);
}
void Memory::insert_instruction(uint32_t address, int32_t machine_instruction[], int i)
{
    instruction_[address] = (new MachineFormat(machine_instruction, i));
}
void Memory::insert_word_to_memory(uint32_t address, uint32_t d)
{
    // std::cout << d << std::endl;
    write_bytes_to_memory(address, d);
}

void Memory::write_bytes_to_memory(uint32_t address, uint32_t x, int size)
{
    unsigned char * p = (unsigned char *) &x;
    if (address - DS_ADDRESS >= 0 && address - DS_ADDRESS < MAX_BUF)
    {
        int start = address - DS_ADDRESS;
        if (start + size > data_size_) data_size_ = start + size;
        for (int i = 0; i < size; ++i)
        {
            data_[i+start] = *(p+i);
        }
    }
    else if (S_ADDRESS - address >= 0 && S_ADDRESS - address < MAX_BUF)
    {
        int start = S_ADDRESS - address;
        if (start + size > stack_size_) stack_size_ = start + size;
        for (int i = 0; i < size; ++i)
        {
            stack_[i+start] = *(p+i);
        }
    }
    else throw std::runtime_error("Invalid Address!!!!");
}

void Memory::write_bytes_to_memory(uint32_t address, const std::string & s)
{
    if (address - DS_ADDRESS >= 0 && address - DS_ADDRESS < MAX_BUF)
    {
        int start = address - DS_ADDRESS;
        if (start + s.size() > data_size_) data_size_ = start + s.size();
        for (int i = 0; i < s.size(); ++i)
        {
            data_[i+start] = s[i];
        }
    }
    else if (S_ADDRESS - address >= 0 && S_ADDRESS - address < MAX_BUF)
    {
        int start = S_ADDRESS - address;
        if (start + s.size() > stack_size_) stack_size_ = start + s.size();
        for (int i = 0; i < s.size(); ++i)
        {
            stack_[i+start] = s[i];
        }
    }
    else throw std::runtime_error("Invalid Address!!!!");
}

void Memory::read_bytes_from_memory(uint32_t address, uint32_t & x, int size)
{
    unsigned char * p = (unsigned char *) &x;
    if (address - DS_ADDRESS >= 0 && address - DS_ADDRESS < MAX_BUF)
    {
        int start = address - DS_ADDRESS;
        
        for (int i = 0; i < size; ++i)
        {
            *(p+i) = data_[i+start];
        }
    }
    else if (S_ADDRESS - address >= 0 && S_ADDRESS - address < MAX_BUF)
    {
        int start = S_ADDRESS - address;
        
        for (int i = 0; i < size; ++i)
        {
            *(p+i) = stack_[i+start];
        }
    }
    else throw std::runtime_error("Invalid Address!!!!");
}

// void Memory::read_bytes_from_memory(uint32_t & address, std::string & s)
// {
//     if (address - DS_ADDRESS >= 0 && DS_ADDRESS - address < MAX_BUF)
//     {
//         int i = address - DS_ADDRESS;
        
//         for (; i < size; ++i)
//         {
//             s[i+1] = data_[i+i];
//         }
//     }
//     else if (S_ADDRESS - address >= 0 && S_ADDRESS - address < MAX_BUF)
//     {
//         int i = S_ADDRESS - address;
        
//         for (; i < size; ++i)
//         {
//             s[i+1] = stack_[i+i];
//         }
//     }
//     else throw std::runtime_error("Invalid Address!!!!");
// }

void Memory::clear()
{
    for (auto p: instruction_)
    {
        delete p.second;
    }
    instruction_.clear();
        
    delete [] data_;
    delete [] stack_;
}

void Memory::print_data(uint32_t address) const
{
    int i = address - DS_ADDRESS;
    // if (i < 0) throw std::runtime_err();
    //std::cout << registers_[4] << ' ' << i << std::endl;
    while (data_[i] != '\0')
    {
        std::cout << std::dec << data_[i++];
    }
}
void Memory::display_data() const
{
    std::cout << "==================================================================\n"
              << "Data Segment\n"
              << "==================================================================\n";
    std::cout << "------------------------------------------------------------------\n"
              << "| addr (int)| addr (hex)| value (int)| value (hex)| value (char) |\n"
              << "------------+-----------+------------+------------+---------------\n";
    
    for (int i = 0; i < data_size_; i += 4)
    {
        // Address in integer
        std::cout << '|';
        std::cout << std::right << std::setw(11) << std::dec << DS_ADDRESS + i << "|";

        // Address in hexidecimal form
        std::cout << std::right << std::setw(11) << std::hex << DS_ADDRESS + i << "|";

        // Value in Interger format
        int value;
        unsigned char * p = (unsigned char *) &value;
        *p = data_[i];
        *(p + 1) = data_[i + 1];
        *(p + 2) = data_[i + 2];
        *(p + 3) = data_[i + 3];
        std::cout << std::right << std::setw(12) << std::dec << value << "|";

        // Value in Hexidecimal form
        std::cout << std::right << std::setw(3) << std::hex << int(data_[i])
                  << std::right << std::setw(3) << std::hex << int(data_[i + 1])
                  << std::right << std::setw(3) << std::hex << int(data_[i + 2])
                  << std::right << std::setw(3) << std::hex << int(data_[i + 3]) << "|";

        // Value in Character form
        std::cout << std::right << std::setw(3);
        print_unsigned_char(data_[i]);
        std::cout << std::right << std::setw(3);
        print_unsigned_char(data_[i + 1]);
        std::cout << std::right << std::setw(3);
        print_unsigned_char(data_[i + 2]);
        std::cout << std::right << std::setw(3);
        print_unsigned_char(data_[i + 3]);
        std::cout << std::right << std::setw(3) << "|";
        std::cout << std::endl;
    }
}
    
void Memory::execute_instruction(uint32_t & PC, RegisterFile & registers)
{
    execute_code(*instruction_[PC], registers, PC, *this);
}
    
