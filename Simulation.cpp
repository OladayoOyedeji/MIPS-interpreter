#include "Simulation.h"

//=================================================================================
// Robert Language Lexer: lexes the instruction for moving into files
//=================================================================================
int Simulation::Robert_Language_lexer(const std::string & command, char * arg,
                                       char * path, int &size)
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
// Read File: 
//=================================================================================
void Simulation::read_file()
{
    std::cout << filename_ << std::endl;
    int option = 0;
    std::ifstream f(filename_, std::ios::in);
    std::string line;
    while (option == 0)
    {
        std::getline(f, line);
        std::cout << line << std::endl;
        std::cout << "\nenter option\n";
                     std::cin >> option;
    }
    f.close();
    
}

//=================================================================================
// Display Current Directory Files
//=================================================================================
void Simulation::display_curdir_files()
{
    char path[FILENAME_MAX];
    GET_CURRENT_DIR(path, sizeof(path));
    int size = len(path);
    bool not_loaded = true;
    int i = 0;

    std::set<std::string> files;
    std::set<std::string> directories;
        
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
        std::cout << len_ << ' ' << command[len_ - 1] << std::endl;
        command[len_] = ' ';
        command[len_ + 1] = '\0';
        
        std::cout << '[' << command << ']' << std::endl;
        
        char file[MAX_BUF] = "";
        int state = Robert_Language_lexer(command, file, path, size);

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
                filename_ = path;
                not_loaded = false;
            }
            else
                std::cout << "File does not exist\n";
        }
       
    }
}

//=================================================================================
// Run Simulation:
//=================================================================================
void Simulation::run_sim(const char * filename)
{
    char option = ' ';

    std::cout << "mips1.0" << std::endl;
    while (true)
    {
        print_option_message();
        std::cin >>option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
        switch (option)
        {
            case 't':
                run_text();
                break;
            case 'd':
                //run_data();
                break;
            case '?':
                // TODO: help instructions
                break;
            case 'p':
                print_system();
                break;
            case 'l':
                display_curdir_files();
                read_file();
                
        }
        if (option == 'q')
        {
            break;
        }
    }
    // ask if they want tp save this to a file
    // TODO: save to file
}

// void Simulation::save_to_file(const char * filename)
// {}

//=================================================================================
// Run Text Segment: to be joined with text segment
//=================================================================================
void Simulation::run_text()
{
    int i = 0;
    int32_t address = TS_ADDRESS;
    while (true)
    {
        // get input
        std::cout << "TEXT:" << "0x" << std::hex << address;
        std::cout << " >";
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
        
        try
        {

            uint32_t address = i * 4 + TS_ADDRESS;
            std::string label = "";
            std::vector< std::string > token;
            
            instruction_lexer(s, token, label);

            process_token(token);
            
            insert_label(label);
        
            if (undefined_label.size() == 0)
            {
                // run_instruction(address);
                for (int i = PC_; i != address; i += 4)
                {
                    std::cout << "0x" << std::hex << i << std::endl;
                }
                PC_ = address;
            }
        
            
        }
        catch (const std::runtime_error & e)
        {
            std::cerr  << e.what() << std::endl;
        }

        print_system();
       
    }
}


//=================================================================================
// Display Registers: TODO name change
//=================================================================================
void Simulation::show_reg() const
{
    std::cout << "==========================================================\n"
              << "Registers\n"
              << "==========================================================\n";
    
    std::map<std::string, int>::const_iterator p = REGISTER_NOMENCLATURE.begin();
    
    std::cout << "$r0| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[0] << " "
              << "$at| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[1] << " "
              << "$v0| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[2] << " "
              << "$v1| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[3] << "\n"
              << "$a0| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[4] << " "
              << "$a1| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[5] << " "
              << "$a2| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[6] << " "
              << "$a3| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[7] << "\n"
              << "$t0| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[8] << " "
              << "$t1| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[9] << " "
              << "$t2| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[10] << " "
              << "$t3| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[11] << "\n"
              << "$t4| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[12] << " "
              << "$t5| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[13] << " "
              << "$t6| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[14] << " "
              << "$t7| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[15] << "\n"
              << "$s0| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[16] << " "
              << "$s1| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[17] << " "
              << "$s2| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[18] << " "
              << "$s3| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[19] << "\n"
              << "$s4| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[20] << " "
              << "$s5| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[21] << " "
              << "$s6| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[22] << " "
              << "$s7| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[23] << "\n"
              << "$t8| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[24] << " "
              << "$t9| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[25] << " "
              << "$k0| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[26] << " "
              << "$k1| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[27] << "\n"
              << "$gp| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[28] << " "
              << "$sp| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[29] << " "
              << "$fp| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[30] << " "
              << "$ra| " << std::right << std::setw(10)
              << std::setfill('0') << registers_[31] << "\n";
}

//=================================================================================
// Prints System: Prints Program Counter, Register, Labels, Data Segment
//=================================================================================
void Simulation::print_system() const
{
    std::cout << "==========================================================\n"
              << "==========================================================\n"
              << " MIPS SYSTEM\n"
              << "==========================================================\n"
              << "==========================================================\n"
              << "Program Counter: " << std::right << std::setw(10)
              << std::setfill('0') << PC_ << std::endl
              << std::endl
              << "HI: " << std::right << std::setw(10)
              << std::setfill('0') << registers_.HI() << std::endl
              << "LO: " << std::right << std::setw(10)
              << std::setfill('0') << registers_.LO() << std::endl;
    show_reg();
    show_labels();
}

//=================================================================================
// Show Labels: 
//=================================================================================
void Simulation::show_labels() const
{
    std::cout << "===============================================\n"
              << "Labels\n"
              << "===============================================\n";

    // auto p = label_.begin();
    // std::cout << typeof(p).name() << std::endl;
    for (auto p: label_)
    {
        std::cout << std::setfill(' ') << std::hex << "0x" << p.second << "| "
                  << std::right << std::setw(20)
                  << p.first << std::endl;
    }

    // TODO: show labels
}

//=================================================================================
// Convert to Machine Format:
//=================================================================================
void Simulation::convert_to_machine_format(std::vector< std::string >& v,
                                           int16_t machine_instruction[], uint32_t address)
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
                machine_instruction[4] = get_label(v[n], address);
                
            }
    }
    
    std::cout << v[0] << " $" << machine_instruction[2] << ", $" << machine_instruction[1]
              << ", " << machine_instruction[4] << std::endl;

}

//=================================================================================
// Insert Label:
//=================================================================================
void Simulation::insert_label(std::string & label, uint32_t address)
{
    if (label != "" && label_.find(label) == label_.end())
    {
        std::cout << "entering\n";
        label_[label] = address;
        if (undefined_label_.find(label) != undefined_label_.end())
        {
            text_[PC_ - TS_ADDRESS]->imm() = address;
            undefined_label_.erase(label);
        }
    }
    else if (label != "")
        throw std::runtime_error("Label already declared");

}

//=================================================================================
// Get Label:
//=================================================================================
int16_t Simulation::get_label(std::string & s, uint32_t address)
{
    if (label_.find(s) != label_.end())
    {
        return (address);
    }
    undefined_label_[s] = address;
    return 0;
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