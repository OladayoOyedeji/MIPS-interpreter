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
    // std::cout << filename_ << std::endl;
    int option = 0;
    std::ifstream f(filename_, std::ios::in);
    std::string line;
    while (option == 0)
    {
        std::getline(f, line);
        // std::cout << line << std::endl;
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
        // std::cout << len_ << ' ' << command[len_ - 1] << std::endl;
        command[len_] = ' ';
        command[len_ + 1] = '\0';
        
        // std::cout << '[' << command << ']' << std::endl;
        
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
                undefined_label_.insert({"main", TS_ADDRESS});
                uint32_t starting_address = TS_ADDRESS;
                while (mode != -1)
                {
                    if (mode == 0)
                    {
                        mode = run_text(starting_address);
                    }
                    else if (mode == 1)
                    {
                        mode = run_data();
                    }
                }
                
        }
        if (option == 'q')
        {
            break;
        }

        // if (mode == 1)
        // {
        //     text = run_text(text_address)
        // }
        // else if (mode == )
        // {
        //     text = run_data()
        // }
        
    }
    // ask if they want tp save this to a file
    // TODO: save to file
}

//=================================================================================
// Get Input: 
//=================================================================================
void Simulation::get_input(std::ifstream & f, std::string & input, bool break_, uint32_t address)
{
    // static std::ifstream f(filename_, std::ios::in);
    if (filename_ == "")
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
        if (f.eof()) break_ = true;
    }
}

// void Simulation::save_to_file(const char * filename)
// {}

//=================================================================================
// Run Text Segment: to be joined with text segment
//=================================================================================
int Simulation::run_text(uint32_t & address)
{
    int i = 0;
    std::ifstream f(filename_, std::ios::in);
    bool break_;
    while (!break_)
    {
        std::string s;
        /*
        // get input
        std::cout << "TEXT:" << "0x" << std::hex << address;
        std::cout << " > ";
        // read string from keyboard and put into input array of characters
        
        std::cin.getline(s, MAX_BUF);
        if (std::cin.eof()) break;
        if (std::cin.fail() || std::cin.bad())
        {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
        '\n');
        }
        */
        
        get_input(f, s, break_, address);
        std::cout << break_ << std::endl;
        std::string label = "";
        std::vector< std::string > token;
            
        instruction_lexer(s, token, label);
        std::cout << "Label: " << label << token << std::endl;
        if (label == "")
        {
            if (token.size() == 1)
            {
                if (strcmp(s, ".data"))
                {
                    return 1;
                }
                else if (strcmp(s, "{print}"))
                {
                    print_system();
                }
            }
        }
        try
        {

            
            
            process_token(token, address);
            insert_label(label, address - 4);
            
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
                    instruction_[PC_]->execute_code(registers_, PC_, data_);
                }
            }
        }
        catch (const std::runtime_error & e)
        {
            if (strcmp(e.what(), "Signal Exception"))
            {
                SignalException();
            }
            else
                std::cerr  << e.what() << std::endl;
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
            std::cout << "Output: "<< registers_[4];
            break;
        case 4:
            i = registers_[4] - DS_ADDRESS;
            // if (i < 0) throw std::runtime_err();
            std::cout << "Output: ";
            while (data_[i] != '\0')
            {
                std::cout << data_[i++];
            }
            break;
        case 5:
            std::cin >> registers_[2];
            break;
        case 10:
            break_ = true;
    }
    PC_ += 4;
    return break_;
}
//=================================================================================
// Run Data:
//=================================================================================
int Simulation::run_data()
{
    while (true)
    {
        // get input
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

        std::string label = "";
        std::vector< std::string > token;
        data_lexer(s, token, label);

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

        // std::cout << token << " Label: " << label<< std::endl;
        insert_label(label, DS_ADDRESS + data_segment_size_);
        if (token.size() != 0)
            process_data_token(token, DS_ADDRESS + data_segment_size_);
        
        // get label

        // divide on space
        // get data typw


        
        
    }
    return -1;
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
              << std::setfill('0') << registers_[31]
              << std::setfill(' ') << "\n";
}

//=================================================================================
// Show Data Segment:
//=================================================================================
void Simulation::show_data() const
{
    std::cout << "==================================================================\n"
              << "Data Segment\n"
              << "==================================================================\n";
    std::cout << "------------------------------------------------------------------\n"
              << "| addr (int)| addr (hex)| value (int)| value (hex)| value (char) |\n"
              << "------------+-----------+------------+------------+---------------\n";
    
        for (int i = 0; i < data_segment_size_; i += 4)
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
        //std::cout << std::endl;
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
    // std::cout << machine_instruction[0] << std::endl;
    int opcode = machine_instruction[0] >> 6;
    int funct = machine_instruction[0] & ((1 << 6) - 1);

    switch (opcode)
    {
        // opcode 0 means it in R format
        case 0:
            // if ()
            // machine_instruction[3] = get_register(v[1]);

            // //std::cout << v.size() << std::endl;
            // // 3 register operation
            // if (v.size() == 4)
            // {
            //     machine_instruction[1] = get_register(v[2]);
            //     machine_instruction[2] = get_register(v[3]);
            // }
            // else
            // {
            //     // shift
            //     machine_instruction[2] = get_register(v[2]);
            //     machine_instruction[5] = get_numeric(v[3]);
            // }
            // // opcode 2 or 3 mean its in j format
            // shift operations
            if (funct >= 0 && funct <= 7)
            {
                if (v.size() != 4)
                {
                    throw std::runtime_error("Invalid instruction");
                }
                machine_instruction[3] = get_register(v[1]);
                machine_instruction[2] = get_register(v[2]);
                machine_instruction[5] = get_numeric(v[3]);
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
            else if (funct == 9)
            {
                if (v.size() != 2)
                {
                    throw std::runtime_error("Invalid instruction");
                }
                machine_instruction[1] = get_register(v[1]);
            }
            // 
            else if (funct >= 24 && funct <= 27)
            {
                if (v.size() != 3)
                {
                    throw std::runtime_error("Invalid instruction");
                }
                machine_instruction[1] = get_register(v[1]);
                machine_instruction[2] = get_register(v[2]);
            }
            else
            {
                machine_instruction[3] = get_register(v[1]);
                machine_instruction[1] = get_register(v[2]);
                machine_instruction[2] = get_register(v[3]);
            }
            break;
        case 2:
        case 3:
            if (v.size() != 2) throw std::runtime_error("Invalid Instruction");
            try{
                machine_instruction[4] = get_numeric(v[1]);
            }
            catch (const std::runtime_error & e){
                machine_instruction[4] = get_label(v[1], address);
            }
            break;

            // others mean I format
        case 4:
        case 5:
            if (v.size() != 4) throw std::runtime_error("Invalid Instruction");
            machine_instruction[1] = get_register(v[1]);
            machine_instruction[2] = get_register(v[2]);
            try{
                machine_instruction[4] = get_numeric(v[3]);
            }
            catch (const std::runtime_error & e)
            {
                machine_instruction[4] = get_label(v[3], address);
            }
            break;
        case 6:
        case 7:
            if (v.size() != 3) throw std::runtime_error("Invalid Instruction");
            machine_instruction[1] = get_register(v[1]);
            try{
                machine_instruction[4] = get_numeric(v[2]);
            }
            catch (const std::runtime_error & e)
            {
                machine_instruction[4] = get_label(v[2], address);
            }
            break;

        case 15:
            if (v.size() != 2) throw std::runtime_error("Invalid Instruction");
            machine_instruction[2] = get_register(v[1]);
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
            machine_instruction[2] = get_register(v[1]);
            
            std::vector<std::string > token;

            get_imm_reg(v[2], token);
            machine_instruction[4] = get_numeric(token[0]);
            machine_instruction[1] = get_register(token[1]);
            break;
            //default:
            // std::cout << v[1] << ' ' << v[2] << std::endl;

            // int n = 1;
            // machine_instruction[2] = get_register(v[n++]);
            // if (v.size() == 4)
            // {
            
            //     machine_instruction[1] = get_register(v[n++]);
            // }

            // try
            // {
            //     machine_instruction[4] = get_numeric(v[n]);
            // }
            // catch (const std::runtime_error & e)
            // {
            //     machine_instruction[4] = get_label(v[n], address);
                
            // }
            
    }
    
    // std::cout << v[0] << " $" << machine_instruction[2] << ", $" << machine_instruction[1]
    //           << ", " << machine_instruction[4] << std::endl;

}

//=================================================================================
// Insert Label:
//=================================================================================
void Simulation::insert_label(std::string & label, uint32_t address)
{
    if (label != "" && label_.find(label) == label_.end())
    {
        // std::cout << "entering\n";
        label_[label] = address;
        if (undefined_label_.find(label) != undefined_label_.end())
        {
            uint32_t key = undefined_label_[label];
            instruction_[key]->imm() = address;
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
    undefined_label_[s] = address;
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
        machine_instruction[0] = OPERATIONS["lui"];
        machine_instruction[1] = 0;
        machine_instruction[2] = get_register("$at");
        machine_instruction[3] = 0;
        machine_instruction[4] = imm >> 16;
        machine_instruction[5] = 0;

        instruction_[address] = (new MachineFormat(machine_instruction));
        address += 4;

        machine_instruction[0] = OPERATIONS["ori"];
        machine_instruction[1] = get_register("$at");
        machine_instruction[2] = get_register(token[1]);
        machine_instruction[3] = 0;
        machine_instruction[4] = imm & ((1 << 16) - 1);
        machine_instruction[5] = 0;
        instruction_[address] = (new MachineFormat(machine_instruction));
        address += 4;
    }
    else if (token[0] == "la")
    {
        if (token.size() != 3)
            throw std::runtime_error("Invalid Instruction");
        
        int imm;

        try
        {
            imm = get_numeric(token[2]);
        }
        catch (std::runtime_error & e)
        {
            imm = get_label(token[2], address);
        }

        int32_t machine_instruction[6];
        machine_instruction[0] = OPERATIONS["lui"];
        machine_instruction[1] = 0;
        machine_instruction[2] = get_register("$at");
        machine_instruction[3] = 0;
        machine_instruction[4] = imm >> 16;
        machine_instruction[5] = 0;
        instruction_[address] = (new MachineFormat(machine_instruction, 1));

        address += 4;

        try
        {
            imm = get_numeric(token[2]);
        }
        catch (std::runtime_error & e)
        {
            imm = get_label(token[2], address);
        }
        
        machine_instruction[0] = OPERATIONS["ori"];
        machine_instruction[1] = get_register("$at");
        machine_instruction[2] = get_register(token[1]);
        machine_instruction[3] = 0;
        machine_instruction[4] = imm & ((1 << 16) - 1);
        machine_instruction[5] = 0;
        instruction_[address] = (new MachineFormat(machine_instruction, 2));
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
        // iteration over list of vectors of strings
        // for (auto p: PSEUDO_INSTRUCTIONS[token[0]])
        // {
        //     // iteration over the vectors of string
        //     std::vector<std::string > & v = p;
        //     for (int i = 0; i < v.size(); ++i)
        //     {
        //         if (v[i].size() == 1 && v[i][0] >= '0' && v[i][0] <= '9')
        //         {
        //             v[i] = token[v[i][0] - '0'];
        //         }
        //     }
        //     // 0:operation_, 1:rs_, 2:rt_, 3:rd_, 4:imm_, 5:shamt_
        //     int32_t machine_instruction[6] = {0};
        //     // std::cout << address << std::endl;
        //     convert_to_machine_format(v, machine_instruction, address);
        //     instruction_[address] = (new MachineFormat(v));
        //     address += 4;
        //     // std::cout << address << std::endl;
        //     // std::cout << v << std::endl;
        // }
        pseudo_to_instruction(token, address);
    }
    else
    {
        try
        {
            // 0:operation_, 1:rs_, 2:rt_, 3:rd_, 4:imm_, 5:shamt_
            int32_t machine_instruction[6] = {0};
            convert_to_machine_format(token, machine_instruction, address);
            instruction_[address] = (new MachineFormat(machine_instruction));
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
            {
                *(data_ + data_segment_size_++) = *(p);
                *(data_ + data_segment_size_++) = *(p+1);
                *(data_ + data_segment_size_++) = *(p+2);
                *(data_ + data_segment_size_++) = *(p+3);
            }
            
            
        }
    }
    else if (strcmp(token[0], ".ascii"))
    {
        for (int i = 1; i < token.size(); ++i)
        {
            for (int j = 0; j < token[i].size(); j++)
            {
                *(data_ + data_segment_size_++) = token[i][j];
            }
        }
    }
}
