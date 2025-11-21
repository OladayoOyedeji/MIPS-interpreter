void insert_label(std::string & label, uint32_t address)
{
    if (label != "" && label_.find(label) == label_.end())
    {
        std::cout << "entering\n";
        label_[label] = address;
        if (undefined_label_.find(label) != undefined_label_.end())
        {
            Instructions[PC_ - TS_ADDRESS]->imm() = address;
            undefined_label.remove(label);
        }
    }
    else if (label != "")
        throw std::runtime_error("Label already declared");

}

int16_t get_label(std::string & s, uin32_t address)
{
    if (label_.find(s) != label_.end())
    {
        return (address - label_[s]);
    }
    undefined_label[s] = address;
    return 0;
}

void convert_to_machine_format(std::vector< std::string >& v, int16_t machine_instruction[])
{
    // get the operation first
    if (OPERATIONS.find(v[0]) != OPERATIONS.end())
    {
        machine_instruction[0] = OPERATIONS[v[0]];
    }
    else
    {
        throw std::runtime_error("Operation not found");
    }
    std::cout << machine_instruction[0] << std::endl;
    int opcode = machine_instruction[0] >> 6;
    int funct = machine_instruction[0] & ((1 << 6) - 1);

    print_bin(opcode, 6);
    std::cout << ' ' ;
    print_bin(funct, 6);
    std::cout << std::endl;

    switch (opcode)
    {
        // opcode 0 means it in R format
        case 0: 
            machine_instruction[3] = get_register(v[1]);

            //std::cout << v.size() << std::endl;
            // 3 register operation
            if (v.size() == 4)
            {
                machine_instruction[1] = get_register(v[2]);
                machine_instruction[2] = get_register(v[3]);
            }
            else
            {
                // shift
                machine_instruction[2] = get_register(v[2]);
                machine_instruction[5] = get_numeric(v[3]);
            }
            // opcode 2 or 3 mean its in j format
            break;
        case 2:
        case 3: break;

            // others mean I format
        default:
            std::cout << v[1] << ' ' << v[2] << std::endl;

            int n = 1;
            machine_instruction[2] = get_register(v[n++]);
            if (v.size() == 4)
            {
            
                machine_instruction[1] = get_register(v[n++]);
            }

            try
            {
                machine_instruction[4] = get_numeric(v[n]);
            }
            catch (const std::runtime_error & e)
            {
                machine_instruction[4] = get_label(v[n]);
                
            }
    }
    
    std::cout << v[0] << " $" << machine_instruction[2] << ", $" << machine_instruction[1]
              << ", " << machine_instruction[4] << std::endl;

}

void run_instruction(uint32_t address)
{
    while (PC_ != address)
    {
        run_code_at(PC);
    }
}

{
    uint32_t end_address = TS_ADDRESS;
    while (1)
    {
        s = get_input();
        std::vector< std::string > token;
        std::string label;
        instruction_lexer(s, token, label);

        // 0:operation_, 1:rs_, 2:rt_, 3:rd_, 4:imm_, 5:shamt_
        int16_t machine_instruction[6] = {0};
        convert_to_machine_format(token, machine_instruction);
        
        insert_instruction(new MachineFormat(machine_instruction));
        
        insert_label(label);
        
        if (undefined_label.size() == 0)
        {
            run_instruction(end_address);
        }
    }
}

{
    instruction_lexer(s, token, label);
    std::cout << "Token: " << token << " Label: " << label << std::endl;
    std::cout << token.size() << std::endl;
            
            
            
// insert label
            
    if (label != "" && label_.find(label) == label_.end())
    {
        std::cout << "entering\n";
        label_[label] = TS_ADDRESS + i * 4;
    }
    else if (label != "")
        throw std::runtime_error("Label already declared");

// insert text_segment
    text_.insert(token);
            
// executing code
    text_.machine_format_[i]->execute_code(registers_);
    PC_ += 4;

    
    i++;
}

void process_token(const std::vector< std::string > & token, uint32_t & address)
{
    if (size_ == MAX_TEXTSEGMENT_SIZE) throw SizeError();

    if (token.size() == 0)
    {
    }
    //===============================================================
    // check if the operation is a pseudo instruction
    //===============================================================
    if (PSEUDO_INSTRUCTIONS.find(token[0]) != PSEUDO_INSTRUCTIONS.end())
    {
        // iteration over list of vectors of strings
        for (auto p: PSEUDO_INSTRUCTIONS[token[0]])
        {
            // iteration over the vectors of string
            std::vector<std::string > & v = p;
            for (int i = 0; i < v.size(); ++i)
            {
                if (v[i].size() == 1 && v[i][0] >= '0' && v[i][0] <= '9')
                {
                    v[i] = token[v[i][0] - '0'];
                }
            }
            // 0:operation_, 1:rs_, 2:rt_, 3:rd_, 4:imm_, 5:shamt_
            int16_t machine_instruction[6] = {0};
            convert_to_machine_format(v, machine_instruction, address);
            instruction_[address] = (new MachineFormat(v));
            address += 4;
            std::cout << v << std::endl;
        }
    }
    else
    {
        try
        {
            // 0:operation_, 1:rs_, 2:rt_, 3:rd_, 4:imm_, 5:shamt_
            int16_t machine_instruction[6] = {0};
            convert_to_machine_format(token, machine_instruction, address);
            instruction_[address] = (new MachineFormat(machine_instruction));
            address += 4;
        }
        catch (const std::runtime_error & e)
        {
            std::cerr << "Invalid Instruction -> " << e.what() << std::endl;
            std::cout << machine_format_.size() << std::endl;
            throw std::runtime_error("Instruction not accepted");
        }
    }
}

}
