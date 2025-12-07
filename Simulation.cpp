#include "Simulation.h"

//=================================================================================
// Robert Language Lexer: lexes the instruction for moving into files
//=================================================================================
int Simulation::Robert_Language_lexer(const std::string & command, char * arg)
{
    // remove trailing spaces, i tracks where non space starts
    int i = 0;
    
    int state = 0;
    while (command[i] == ' ')
    {
        if (command[i++] == '\0')
        {
            return -1;
        }
    }
    if (command[i] == '<' && command[i + 1] == '-')
    {
        return 2;
    }
    else
    {
        int instruction_state = 0;

        int j = i;
        while (command[j] != '\0')
        {
            // instruction_state 0: gets the name of the instruction,
            // instruction_state 1: what should file or dir should be on
            // might not do instruction_state 2 cause its too harsh
            // instruction_state 2: check for other syntax issues

            // std::cout << command[j] << std::endl;
            if (command[j] == ' ' || command[j] == '\t')
            {
                //std::cout << "here? " << instruction_state << std::endl;
                if (command[i] == ' ' || command[i] == '\t')
                {
                    i = j++;
                    continue;
                }
                //std::cout << instruction_state << std::endl;
                if (instruction_state == 0)
                {
                    //std::cout << '[' << command.substr(i, j-i) << ']' << std::endl;
                    if (strcmp(command.substr(i, j-i), "lf"))
                    {
                        //std::cout << "load a file" << std::endl;
                        state = 0;
                    }
                    else if (strcmp(command.substr(i, j - i), "move"))
                    {
                        //std::cout << "move into a directory" << std::endl;
                        state = 1;
                    }
                    else return -1;
                }
                else if (instruction_state == 1)
                {
                    //std::cout << "step 2\n";
                    //arg = command.substr(i, j - i);
                    for (int k = i; k != j; ++k)
                    {
                        arg[k - i] = command[k];
                    }
                    arg[j - i] = '\0';
                    return state;
                }
                i = j + 1;
                instruction_state++;
            }
            j++;
        }
         
    }
    return state;
}

//=================================================================================
// Display Current Directory Files
//=================================================================================
void Simulation::display_curdir_files()
{
    // char path[FILENAME_MAX];
    // GET_CURRENT_DIR(path, sizeof(path));
    int size = filepath_.size();
    bool not_loaded = true;
    int i = 0;

    std::set<std::string> files;
    std::set<std::string> directories;
    char path[1024];
    for (int i = 0; i < filepath_.size(); ++i)
    {
        path[i] = filepath_[i];
    }

    path[filepath_.size()] = '\0';
    
    while (not_loaded)
    {
        std::cout << path << std::endl;
        // print files and directory in the directory
        for (const auto& entry : fs::directory_iterator(path))
        {
            // Check if the entry is a regular file
            if (fs::is_regular_file(entry.status()))
            {
                std::cout << "\033[33;44m";
                files.insert(entry.path().filename().string());
            }
            else
            {
                std::cout << "\033[1;37;40m";
                directories.insert(entry.path().filename().string());
            }
            std::cout << entry.path().filename().string() << ' ' << "\033[0m ";
            // Print only the filename
                
        }
        std::cout << "<-" << std::endl;

        // get a command
        char command[MAX_BUF] = "";
        //
        std::cout << ">> ";
        std::cin.getline(command, MAX_BUF);
        
        if (std::cin.eof()) break;
        if (std::cin.fail() || std::cin.bad())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
        }

        int len_ = len(command);
        // std::cout << len_ << ' ' << command[len_ - 1] << std::endl;
        command[len_] = ' ';
        command[len_ + 1] = '\0';
        
        // std::cout << '[' << command << ']' << std::endl;
        
        char file[MAX_BUF] = "";
        int state = Robert_Language_lexer(command, file);

        //std::cout << state << " [" << file << ']' << std::endl;;
        
        if (state == -1)
        {
            std::cout << "dude know my syntax\n";
        }
        else if (state == 2)
        {
            for (; size >= 0; --size)
            {
                if (path[size] == '/')
                {
                    path[size] = '\0';
                    break;
                }
            }
            size = len(path);
        }
        else if (state == 1)
        {
            if (directories.find(file) != directories.end() || file == "")
            {
                append_to_path(path, size, file);
            }
            else
                std::cout << "Directory does not exist\n";
        }
        else if (state == 0)
        {
            if (files.find(file) != files.end())
            {
                // append dir to path
                append_to_path(path, size, file);
                filepath_ = path;
                not_loaded = false;
            }
            else
            {
                std::cout << "File does not exist\n";
            }
        }
        
        files.clear();
        directories.clear();
    }
    filepath_ = path;
}

void Simulation::reinitialize_sim()
{
    // for (auto p: instruction_)
    // {
    //     delete p.second;
    // }
    // instruction_.clear();
    
    // delete [] data_;
    // data_ = new unsigned char[1024];
    // for (int i = 0; i < data_segment_size_; ++i)
    // {
    //     data_[i] = 0;
    // }
    
    // data_segment_size_ = 0;
    memory_.clear();
    label_.clear();
    undefined_label_.clear();
    PC_ = TS_ADDRESS;
    registers_ = RegisterFile();

    memory_ = Memory();

}

//=================================================================================
// Run Simulation:
//=================================================================================
void Simulation::run_sim(const char * filename)
{
    char option = ' ';

    std::cout << "MIPS interpreter 1.0" << std::endl;
    while (true)
    {
        print_option_message();
        std::cout << ">>>> ";
        std::cin >>option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n');
        int mode;
        if (option == 's')
        {
            uint32_t starting_address = TS_ADDRESS;
          text: mode = run_text(starting_address);
            if (mode == 1)
            {
                mode = run_data();
                if (mode == 0)
                {
                    goto text;
                }
            }
            // print_system();
            
            reinitialize_sim();
        }
        switch (option)
        {
            case 't':
                // run_text();
                break;
            case 'd':
                //run_data();
                break;
            case '?':
                // TODO: help instructions
                std::cout << "Write Mips assembly code on the live terminal or load a file for execution\n"
                          << "\t-Live: Code written on the live intepreter are ran as they are written, \n"
                          << "\t       write \"{print}\" to print the system whenever you want to view the entire system\n"
                          << "\t       User can switch from text segment to data segment by writing .text and .data respectively\n"
                          << "\t-Run File: User can run a mips assembly file,\n"
                          << "\t       write \"<-\" to go to the parent directory,\n"
                          << "\t       write \"move {directory_name}\" to move into desired directory\n"
                          << "\t       write \"lf {filename}\" to load desired assemble file\n" ;
                break;
            case 'l':
                display_curdir_files();
                //read_file();
                mode = 0;
                // undefined_label_.insert({"main", TS_ADDRESS});
                std::string label = "";
                std::vector< std::string > token;
                instruction_lexer("j main", token, label);
                uint32_t starting_address = TS_ADDRESS;
                process_token(token, starting_address);
                starting_address += 4;
                std::ifstream f(filepath_, std::ios::in);
                
                while (mode != -1)
                {
                    if (mode == 0)
                    {
                        mode = run_text(starting_address, &f);
                    }
                    else if (mode == 1)
                    {
                        mode = run_data(&f);
                    }
                }
                print_system();
                reinitialize_sim();
                
        }
        if (option == 'q')
        {
            break;
        }
    }
    // ask if they want tp save this to a file
    // TODO: save to file
}

//=================================================================================
// Get Input: 
//=================================================================================
void Simulation::get_input(std::ifstream & f, std::string & input, bool & break_, uint32_t address, bool live)
{
    // static std::ifstream f(filepath_, std::ios::in);
    if (live)
    {
        // get input
        char s[1024];
        std::cout << "TEXT:" << "0x" << std::hex << address;
        std::cout << " > ";
        // read string from keyboard and put into input array of characters
        
        std::cin.getline(s, MAX_BUF);
        if (std::cin.eof()) break_ = true;
        if (std::cin.fail() || std::cin.bad())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
        }
        input = std::string(s);
    }
    else
    {
        std::getline(f, input);
        if (f.eof()) {break_ = true;}
    }
}

// void Simulation::save_to_file(const char * filename)
// {}

//=================================================================================
// Run Text Segment: to be joined with text segment
//=================================================================================
int Simulation::run_text(uint32_t & address, std::ifstream * f)
{
    int i = 0;
    bool break_ = false;
    // std::cout << f << std::endl;
    while (!break_)
    {
        std::string s;
        
        get_input(*f, s, break_, address, f == NULL);
        // std::cout << break_ << std::endl;
        std::string label = "";
        std::vector< std::string > token;
        
        instruction_lexer(s, token, label);
        // std::cout << "Label: " << label << ": " << token << std::endl;
        // print_system();
        if (label == "" && token.size() == 1 && strcmp(token[0], ".data"))
        {
            // std::cout << "data" << std::endl;
            return 1;
        }
        else if (label == "" && token.size() == 1 && strcmp(token[0], ".text"))
        {
            // std::cout << "data" << std::endl;
            continue;
        }
        else if (label == "" && token.size() == 1 && strcmp(s, "{print}"))
        {
            print_system();
            continue;
        }
        else if (label == "" && token.size() == 1 && strcmp(s, ".text"))
        {
            return 0;
        }
        else if (label == "" && token.size() == 2 && strcmp(token[0], ".globl"))
        {
            continue;
        }
        
        // std::cout << "Label: " << label << token << std::endl;
        
        try
        {
            uint32_t label_address = address;
            // std::cout << "address at label: " << label_address << std::endl;
            process_token(token, address);
            insert_label(label, label_address);
            
            // std::cout << "Undefined Label size: " << undefined_label_.size() << std::endl;
            if (undefined_label_.size() == 0)
            {
                // run_instruction(address);
                // for (int i = PC_; i != address; i += 4)
                // {
                //     std::cout << "0x" << std::hex << i << std::endl;
                // }
                
                while (PC_ != address)
                {
                    
                    // std::cout << PC_ << " address: " << address << std::endl;
                    // instruction_[PC_]->execute_code(registers_, PC_, data_, data_segment_size_);
                    memory_.print_instruction(PC_);
                    memory_.execute_instruction(PC_, registers_);
                    // print_system();
                }
            }
        }
        catch (const std::runtime_error & e)
        {
            if (strcmp(e.what(), "Signal Exception"))
            {
                break_ = SignalException();
            }
            else
            {
                std::cerr  << e.what() << std::endl;
                
                std::cout << "0x" << std::hex << address;
                std::cout << " > ";
                std::cout << "Label: " << label << ' ' << token << std::endl;
                return -1;
            }
        }
        
    }
    return -1;
}

bool Simulation::SignalException()
{
    int i;
    bool break_ = false;
    switch (registers_[2])
    {
        case 1:
            std::cout << std::dec << registers_[4];
            break;
        case 4:
            // std::cout << registers_[4] << std::endl;
            memory_.print_data(registers_[4]);
            break;
        case 5:
            std::cin >> i;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
            registers_[2] = i;
            break;
        case 8:
        {
            char s[1024];
            std::cin.getline(s, MAX_BUF);
            if (std::cin.eof()) break_ = true;
            if (std::cin.fail() || std::cin.bad())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');
            }
            uint32_t address = DS_ADDRESS + memory_.data_size();
            std::string args(s);
            memory_.write_bytes_to_memory(address, args);
            registers_[4] = address;
            break;
        }   
        case 10:
            break_ = true;
    }
    PC_ += 4;
    return break_;
}
//=================================================================================
// Run Data:
//=================================================================================
int Simulation::run_data(std::ifstream * f)
{
    bool break_ = false;
    while (!break_)
    {
        // get input
        std::string s;
        /*
        std::cout << "DATA:" << "0x" << std::hex << DS_ADDRESS + data_segment_size_;
        std::cout << " > ";
        // read string from keyboard and put into input array of characters
        
        char s[MAX_BUF];
        std::cin.getline(s, MAX_BUF);
        if (std::cin.eof()) break;
        if (std::cin.fail() || std::cin.bad())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
        }
        */
        uint32_t address = DS_ADDRESS + memory_.data_size();
        get_input(*f, s, break_, address, f == NULL);
        
        std::string label = "";
        std::vector< std::string > token;
        try
        {
            data_lexer(s, token, label);

            // std::cout << token << " Label: " << label<< std::endl;

            if (label == "" && token.size() == 1)
            {
                if (strcmp(s, ".text"))
                {
                    return 0;
                }
                else if (strcmp(s, "{print}"))
                {
                    print_system();
                }
            }
            insert_label(label, address);
            // std::cout << "where am i?" << std::endl;
            if (token.size() != 0)
                process_data_token(token, address);
        }
        catch (std::runtime_error & e)
        {
            std::cerr << "data: " << e.what() << std::endl;
            std::cout << token << std::endl;
        }
        // get label

        // divide on space
        // get data typw


        
        
    }
    return 0;
}

//=================================================================================
// Display Registers: TODO name change
//=================================================================================
void Simulation::show_reg() const
{
    registers_.display_reg();
}

//=================================================================================
// Show Data Segment:
//=================================================================================
void Simulation::show_data() const
{
    memory_.display_data();
}

//=================================================================================
// Prints System: Prints Program Counter, Register, Labels, Data Segment
//=================================================================================
void Simulation::print_system() const
{
    std::cout << "==================================================================\n"
              << "==================================================================\n"
              << " MIPS SYSTEM\n"
              << "==================================================================\n"
              << "==================================================================\n"
              << "Program Counter: " << std::right
              << std::setfill(' ') << "0x" << std::hex << PC_ << std::endl
              << std::endl
              << "HI: " << std::right
              << std::setfill(' ') << "0x" << std::hex << registers_.HI() << std::endl
              << "LO: " << std::right
              << std::setfill(' ') << "0x" << std::hex << registers_.LO() << std::endl;
    show_reg();
    show_labels();
    show_data();
}

//=================================================================================
// Show Labels: 
//=================================================================================
void Simulation::show_labels() const
{
    std::cout << "===================================================================\n"
              << "Labels\n"
              << "===================================================================\n";

    // auto p = label_.begin();
    // std::cout << typeof(p).name() << std::endl;
    for (auto p: label_)
    {
        std::cout << std::setfill(' ') << std::hex << "0x" << p.second << "| "
                  << std::right << std::setw(20)
                  << p.first << std::endl;
    }

     std::cout << "===================================================================\n"
              << "Undefined Labels\n"
              << "===================================================================\n";

     // auto p = label_.begin();
     // std::cout << typeof(p).name() << std::endl;
     for (auto p: undefined_label_)
     {
         for (auto q: p.second)
         {
             std::cout << std::setfill(' ') << std::hex << "0x" << q << "| "
                       << std::right << std::setw(20)
                       << p.first << std::endl;
        }
    }

    // TODO: show labels
}

//=================================================================================
// Convert to Machine Format:
//=================================================================================
void Simulation::convert_to_machine_format(const std::vector< std::string >& v,
                                           int32_t machine_instruction[], uint32_t address)
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
    // std::cout << machine_instruction[OPFUNCT] << std::endl;
    int opcode = machine_instruction[OPFUNCT] >> 6;
    int funct = machine_instruction[OPFUNCT] & ((1 << 6) - 1);

    switch (opcode)
    {
        // not part of the pattern

        // mul R-format but opcode of 0
        case 28:
            // std::cout << "mul\n";
            if (v.size() != 4) throw std::runtime_error("Invalid Instruction");
            machine_instruction[RD] = get_register(v[1]);
            machine_instruction[RS] = get_register(v[2]);
            machine_instruction[RT] = get_register(v[3]);
            break;
        // opcode 0 means it in R format
        case 0:
            // shift operations
            if (funct >= 0 && funct <= 7)
            {
                if (v.size() != 4)
                {
                    throw std::runtime_error("Invalid instruction");
                }
                machine_instruction[RD] = get_register(v[1]);
                machine_instruction[RT] = get_register(v[2]);
                machine_instruction[SHAMT] = get_numeric(v[3]);
            }
            // syscall operation
            else if (funct == 12)
            {
                if (v.size() != 1)
                {
                    throw std::runtime_error("Invalid instruction");
                }
            }
            // jr operation
            else if (funct == 8 || funct == 9 || funct == 17 || funct == 19)
            {
                if (v.size() != 2)
                {
                    throw std::runtime_error("Invalid instruction");
                }
                machine_instruction[RS] = get_register(v[1]);
            }
            else if (funct == 16 || funct == 18)
            {
                if (v.size() != 2)
                {
                    throw std::runtime_error("Invalid instruction");
                }
                machine_instruction[RD] = get_register(v[1]);
            }
            // 
            else if (funct >= 24 && funct <= 27)
            {
                if (v.size() != 3)
                {
                    throw std::runtime_error("Invalid instruction");
                }
                machine_instruction[RS] = get_register(v[1]);
                machine_instruction[RT] = get_register(v[2]);
            }
            else
            {
                if (v.size() != 4) throw std::runtime_error("Invalid Instruction");
                machine_instruction[RD] = get_register(v[1]);
                machine_instruction[RS] = get_register(v[2]);
                machine_instruction[RT] = get_register(v[3]);
            }
            break;
        case 2:
        case 3:
            if (v.size() != 2) throw std::runtime_error("Invalid Instruction");
            try{
                machine_instruction[IMM] = get_numeric(v[1]);
            }
            catch (const std::runtime_error & e){
                machine_instruction[IMM] = get_label(v[1], address);
            }
            break;

            // others mean I format
        case 4:
        case 5:
            if (v.size() != 4) throw std::runtime_error("Invalid Instruction");
            machine_instruction[RS] = get_register(v[1]);
            machine_instruction[RT] = get_register(v[2]);
            try{
                machine_instruction[IMM] = get_numeric(v[3]);
            }
            catch (const std::runtime_error & e)
            {
                machine_instruction[IMM] = get_label(v[3], address);
            }
            break;
        case 6:
        case 7:
            if (v.size() != 3) throw std::runtime_error("Invalid Instruction");
            machine_instruction[RS] = get_register(v[1]);
            try{
                machine_instruction[IMM] = get_numeric(v[2]);
            }
            catch (const std::runtime_error & e)
            {
                machine_instruction[IMM] = get_label(v[2], address);
            }
            break;
        case 8:
        case 9:
        case 11:
            if (v.size() != 4) throw std::runtime_error("Invalid Instruction");
            machine_instruction[RT] = get_register(v[1]);
            machine_instruction[RS] = get_register(v[2]);
            machine_instruction[IMM] = get_numeric(v[3]);
            break;
        case 15:
            if (v.size() != 2) throw std::runtime_error("Invalid Instruction");
            machine_instruction[RT] = get_register(v[1]);
            break;
        case 32:
        case 33:
        case 35:
        case 36:
        case 37:
        case 43:
        case 41:
        case 40:
            if (v.size() != 3) throw std::runtime_error("Invalid Instruction");
            machine_instruction[RT] = get_register(v[1]);
            
            std::vector<std::string > token;

            get_imm_reg(v[2], token);
            machine_instruction[IMM] = get_numeric(token[0]);
            machine_instruction[RS] = get_register(token[1]);
            break;
    }
}

//=================================================================================
// Insert Label:
//=================================================================================
void Simulation::insert_label(std::string & label, uint32_t address)
{
    // std::cout << lebel_.find(label) << std
    if (label != "" && label_.find(label) == label_.end())
    {
        // std::cout << "entering\n";
        label_[label] = address;
        // std::cout << label << std::endl;
        if (undefined_label_.find(label) != undefined_label_.end())
        {
            // std::cout << "dude " << label << std::endl;
            
            for (auto p: undefined_label_[label])
            {
                uint32_t key = p;
                // instruction_[key]->insert_imm(address);
                memory_.insert_imm(key, address);
            }
            
            undefined_label_.erase(label);
        }
    }
    else if (label != "")
        throw std::runtime_error("Label already declared");

}

//=================================================================================
// Get Label:
//=================================================================================
int32_t Simulation::get_label(const std::string & s, uint32_t address)
{
    if (label_.find(s) != label_.end())
    {
        return label_[s];
    }
    undefined_label_[s].push_front(address);
    return 0;
}

void Simulation::pseudo_to_instruction(const std::vector< std::string > & token, uint32_t & address)
{
    if (token[0] == "li")
    {
        if (token.size() != 3)
            throw std::runtime_error("Invalid Instruction");
        
        int imm;
        
        imm = get_numeric(token[2]);
        
        int32_t machine_instruction[6];
        machine_instruction[OPFUNCT] = OPERATIONS["lui"];
        machine_instruction[RS] = 0;
        machine_instruction[RT] = get_register("$at");
        machine_instruction[RD] = 0;
        machine_instruction[IMM] = imm >> 16;
        machine_instruction[SHAMT] = 0;

        // instruction_[address] = (new MachineFormat(machine_instruction));
        memory_.insert_instruction(address, machine_instruction);
        
        address += 4;

        machine_instruction[OPFUNCT] = OPERATIONS["ori"];
        machine_instruction[RS] = get_register("$at");
        machine_instruction[RT] = get_register(token[1]);
        machine_instruction[RD] = 0;
        machine_instruction[IMM] = imm & ((1 << 16) - 1);
        machine_instruction[SHAMT] = 0;
        registers_[get_register(token[1])].print_signed_ = true;
        // instruction_[address] = (new MachineFormat(machine_instruction));
        memory_.insert_instruction(address, machine_instruction);
        
        address += 4;
    }
    else if (token[0] == "la")
    {
        if (token.size() != 3)
            throw std::runtime_error(
                "Invalid Instruction");
        
        int imm;

        try
        {
            imm = get_numeric(token[2]);
        }
        catch (std::runtime_error & e)
        {
            imm = get_label(token[2], address);
        }
        // std::cout << imm << std::endl;

        int32_t machine_instruction[6];
        machine_instruction[OPFUNCT] = OPERATIONS["lui"];
        machine_instruction[RS] = 0;
        machine_instruction[RT] = get_register("$at");
        machine_instruction[RD] = 0;
        machine_instruction[IMM] = imm >> 16;
        machine_instruction[SHAMT] = 0;
        
        // instruction_[address] = (new MachineFormat(machine_instruction, 1));
        memory_.insert_instruction(address, machine_instruction, 1);

        address += 4;

        try
        {
            imm = get_numeric(token[2]);
        }
        catch (std::runtime_error & e)
        {
            imm = get_label(token[2], address);
        }
        
        machine_instruction[OPFUNCT] = OPERATIONS["ori"];
        machine_instruction[RS] = get_register("$at");
        machine_instruction[RT] = get_register(token[1]);
        machine_instruction[RD] = 0;
        machine_instruction[IMM] = imm & ((1 << 16) - 1);
        machine_instruction[SHAMT] = 0;
        registers_[get_register(token[1])].print_signed_ = false;
        // instruction_[address] = (new MachineFormat(machine_instruction, 2));
        memory_.insert_instruction(address, machine_instruction, 2);
            
        address += 4;
    }
    else if (token[0] == "move")
    {
        int32_t machine_instruction[6];
        machine_instruction[OPFUNCT] = OPERATIONS["add"];
        machine_instruction[RS] = get_register(token[2]);
        machine_instruction[RT] = 0;
        machine_instruction[RD] = get_register(token[1]);
        machine_instruction[IMM] = 0;
        machine_instruction[SHAMT] = 0;
        
        // instruction_[address] = (new MachineFormat(machine_instruction, 2));
        memory_.insert_instruction(address, machine_instruction, 2);
        
        address += 4;
    }
    else if (token[0] == "beqz" || token[0] == "bnez")
    {
        int imm;

        try
        {
            imm = get_numeric(token[2]);
        }
        catch (std::runtime_error & e)
        {
            imm = get_label(token[2], address);
        }
        const std::string inst = token[0].substr(0, 3);
        int32_t machine_instruction[6];
        machine_instruction[OPFUNCT] = OPERATIONS[inst];
        machine_instruction[RS] = get_register(token[1]);
        machine_instruction[RT] = 0;
        machine_instruction[RD] = 0;
        machine_instruction[IMM] = imm;
        machine_instruction[SHAMT] = 0;
        
        // instruction_[address] = (new MachineFormat(machine_instruction));
        memory_.insert_instruction(address, machine_instruction);
        
        address += 4;
    }
    else if (token[0] == "blt" || token[0] == "ble" ||
             token[0] == "bge" || token[0] == "bgt")
    {
        std::string inst1;
        if (token[0] == "bgt" || token[0] == "blt")
        {
            inst1 = "bne";
        }
        else
        {
            inst1 = "beq";
        }

        int32_t machine_instruction[6];
        // std::cout << token << std::endl;
        machine_instruction[OPFUNCT] = OPERATIONS["slt"];
        machine_instruction[RS] = get_register(token[1]);
        machine_instruction[RT] = get_register(token[2]);
        // $at = $1
        if (token[0] == "bgt" || token[0] == "ble")
        {
            int32_t t = machine_instruction[RS];
            machine_instruction[RS] = machine_instruction[RT];
            machine_instruction[RT] = t;
        }
        machine_instruction[RD] = get_register("$at");

        // instruction_[address] = (new MachineFormat(machine_instruction));
        memory_.insert_instruction(address, machine_instruction);
        
        address += 4;

        int imm;

        try
        {
            imm = get_numeric(token[3]);
        }
        catch (std::runtime_error & e)
        {
            imm = get_label(token[3], address);
        }
        
        machine_instruction[OPFUNCT] = OPERATIONS[inst1];
        machine_instruction[RS] = get_register("$at");
        machine_instruction[RT] = 0;
        machine_instruction[RD] = 0;
        machine_instruction[IMM] = imm;
        machine_instruction[SHAMT] = 0;
        
        // instruction_[address] = (new MachineFormat(machine_instruction));
        memory_.insert_instruction(address, machine_instruction);
        
        address += 4;
    }
    else if (token[0] == "seq")
    {
        int32_t machine_instruction[6];
        // std::cout << token << std::endl;
        machine_instruction[OPFUNCT] = OPERATIONS["xor"];
        machine_instruction[RD] = get_register(token[1]);
        machine_instruction[RS] = get_register(token[2]);
        machine_instruction[RT] = get_register(token[3]);
        machine_instruction[IMM] = 1;
        machine_instruction[SHAMT] = 0;

        // instruction_[address] = (new MachineFormat(machine_instruction));
        memory_.insert_instruction(address, machine_instruction);
        
        address += 4;

        machine_instruction[OPFUNCT] = OPERATIONS["sltiu"];
        machine_instruction[RS] = get_register(token[1]);
        machine_instruction[RT] = get_register(token[1]);
        machine_instruction[RD] = 0;
        machine_instruction[IMM] = 1;
        machine_instruction[SHAMT] = 0;
        
        // instruction_[address] = (new MachineFormat(machine_instruction));
        memory_.insert_instruction(address, machine_instruction);
        
        address += 4;
    }
}

//=================================================================================
// Process Token:
//=================================================================================
void Simulation::process_token(const std::vector< std::string > & token, uint32_t & address)
{
    // if (size_ == MAX_TEXTSEGMENT_SIZE) throw SizeError();

    // std::cout << token.size() << std::endl;
    if (token.size() == 0)
    {
        return;
    }
    //===============================================================
    // check if the operation is a pseudo instruction
    //===============================================================
    if (PSEUDO_INSTRUCTIONS.find(token[0]) != PSEUDO_INSTRUCTIONS.end())
    {
        pseudo_to_instruction(token, address);
        
    }
    else
    {
        try
        {
            // 0:operation_, 1:rs_, 2:rt_, 3:rd_, 4:imm_, 5:shamt_
            int32_t machine_instruction[6] = {0};
            convert_to_machine_format(token, machine_instruction, address);
            
            // instruction_[address] = (new MachineFormat(machine_instruction));
            memory_.insert_instruction(address, machine_instruction);
            
            address += 4;
        }
        catch (const std::runtime_error & e)
        {
            std::cerr << "Invalid Instruction -> " << e.what() << std::endl;
            // std::cout << machine_format_.size() << std::endl;
            throw std::runtime_error("Instruction not accepted");
        }
    }
}

//=================================================================================
// Process Data Token:
//=================================================================================
void Simulation::process_data_token(const std::vector< std::string > & token, uint32_t address)
{
    if (strcmp(token[0], ".word"))
    {
        for (int i = 1; i < token.size(); ++i)
        {
            int word;
            unsigned char * p = (unsigned char *) &word;
            try
            {
                word = get_numeric(token[i]);
            }
            catch (const std::runtime_error & e)
            {
                word = get_label(token[i], address);
                if (word == 0) return;
            }
            memory_.insert_word_to_memory(address, word);
            address += 4;
        }
    }
    else if (strcmp(token[0], ".ascii"))
    {
        for (int i = 1; i < token.size(); ++i)
        {
            // for (int j = 0; j < token[i].size(); j++)
            // {
            //     *(data_ + data_segment_size_++) = token[i][j];
            // }
            memory_.write_bytes_to_memory(address, token[i]);
            address += token[i].size();
        }
    }
    else if (strcmp(token[0], ".asciiz"))
    {
        for (int i = 1; i < token.size(); ++i)
        {
            // for (int j = 0; j < token[i].size(); j++)
            // {
            //     *(data_ + data_segment_size_++) = token[i][j];
            // }
            memory_.write_bytes_to_memory(address, token[i]);
            
            address += token[i].size();
            memory_.write_a_byte_to_memory(address, '\0');
            address++;
        }
        
    }
    else if (strcmp(token[0], ".byte"))
    {
        for (int i = 1; i < token.size(); ++i)
        {
            unsigned char byte;
            try
            {
                byte = get_numeric(token[i]);
            }
            catch (const std::runtime_error & e)
            {
                byte = get_label(token[i], address);
            }
            memory_.write_a_byte_to_memory(address, byte);
            address++;
        }
    }
    else if (strcmp(token[0], ".space"))
    {
        for (int i = 1; i < token.size(); ++i)
        {
            int size;
            try
            {
                size = get_numeric(token[i]);
            }
            catch (const std::runtime_error & e)
            {
                size = get_label(token[i], address);
            }
            
            for (int j = 0; j < size; ++j)
            {
                memory_.write_a_byte_to_memory(address, '\0');
                address++;
            }
        }
    }
}
