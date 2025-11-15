#ifndef MACHINE_FORMAT_H
#define MACHINE_FORMAT_H

// void get_operation_type(const std::string & s, int32_t & operation,
//                         int32_t & type)
// {
//     if (s == "lui")
//     {
//         operation = (7 << 5);
//         type = 1;
//         return;
//     }
//     if (s == "ori")
//     {
//         operation = (48 << 5);
//         type = 1;
//         return;
//     }
// }

class MachineFormat
{
public:
    // assuming we have removed the label on it
    // and trailing zeros are gone
    MachineFormat(const std::vector< std::string > & v)
    {
        // get the operation first
        

        // get_operation_type(v[0], operation_, type_);
        // switch (type_)
        // {
        //     case 0:
        //         rd_ = get_register(v[1]);
        //         rs_ = get_register(v[2]);
        //         rt_ = get_register(v[3]);
                
        //     case 1:
        //         rt_ = get_register(v[1]);
        //         rs_ = get_register(v[2]);
        //         imm_ = get_numeric(v[3]);
        //     case 2:
        // }
    }
private:
    int32_t operation_;
    int32_t rs_;
    int32_t rt_;
    int32_t rd_;
    int32_t shamt_;

    std::string instruction_;
};



#endif
