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

int get_register(const std::string & s)
{
    if (REGISTER_NOMENCLATURE.find(s) != REGISTER_NOMENCLATURE.end())
    {
        // std::cout << "here?\n" << "rt" << s << ' '
        //           << REGISTER_NOMENCLATURE[s] << std::endl;
        return REGISTER_NOMENCLATURE[s];
    }
    else if (s.size() == 2 && s[0] == '$' && s[1] >= '0' && s[1] <= '9')
    {
        // std::cout << "no here?\n" << "rt" << s << ' ' << s[1] << std::endl;;
        return (s[1] - '0');
    }
    else
    {
        // std::string error_message = "Register ";
        // error_message.push_back(s);
        // error_message.push_back("not found");
        throw std::runtime_error("Register not found");
    }
    return -1;
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
    std::cout << operation_ << std::endl;
    int opcode = operation_ >> 6;
    int funct = operation_ & ((1 << 6) - 1);

    print_bin(opcode, 6);
    std::cout << ' ' ;
    print_bin(funct, 6);
    std::cout << std::endl;

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
        case 3: break;

            // others mean I format
        default:
            std::cout << v[1] << ' ' << v[2] << std::endl;

            rt_ = get_register(v[1]);
            
            rs_ = get_register(v[2]);

            imm_ = get_numeric(v[3]);
 
            std::cout << v[0] << " $" << rt_ << ", $" << rs_ << ", " << imm_ << std::endl;
    }
}

void MachineFormat::execute_code(RegisterFile & r)
{
    switch (operation_)
    {
        // case ADD:
        case 32:
            std::cout << r[rs_] << ' ' << r[rt_] << std::endl;
            r[rd_] = r[rs_] + r[rt_];
            break;
        // CASE ORI:
        case 832:
            
            r[rt_] = r[rs_] | imm_;
            //std::cout << r[rt_] << std::endl;
            
            break;
    }
}
