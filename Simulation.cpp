#include "Simulation.h"

void append_to_path(char * path, int & size, const char * file="")
{
    // append dir to path
    std::cout << "herro? [" << path[size - 2] << ']' << std::endl;
    path[size++] = '/';
    int i = 0;
    while (true)
    {
        std::cout << '[' << path << "] " << file[i] << std::endl;
        path[size] = file[i];
        if (file[i++] == '\0') break;
        size++;
    }
    std::cout << '[' << path << "] " << std::endl;
}

// state 1:go into a directory, state 2:gone back, state 0:file loaded, state -1:error in the syntax
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
        
        //if (state )
        // instruction[3]
        // if ()
        //std::cout << i++ << std::endl;
        //std::cout << "enter option" << std::endl;
        //std::cin >> option;
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
        //                '\n');
    }
}

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
                show_reg();
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

void Simulation::run_text()
{
    int i = 0;
    while (true)
    {
        std::cout << "TEXT:";
        text_.print_addressh(i);
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

        // TODO: get label
        
        // insert text
        std::cout << s << std::endl;
        text_.insert(s);
        std::cout << "done" << std::endl;
            
        i++;
        // if (token(s))
        // {
        // // tokenize instruction
        // // and instruction can be divided into label, instruction and registers,
        // // or instruction to be
        // // Also if psuedo instruction divide into instructions
            
        // }
    }
}

// void Simulation::run_data()
// {
// }

void Simulation::show_reg()
{
    std::cout << "======================================================================================================\n"
              << "Registers\n"
              << "======================================================================================================\n";
    std::map<std::string, int>::const_iterator p = REGISTER_NOMENCLATURE.begin();
    for (int i = 0; i < 32; ++i)
    {
        std::cout << p->first << "| ";
        std::cout << std::right << std::setw(20)
                  << std::setfill('0') << registers_[i] << " ";

        if ((i + 1) % 4 == 0)
        {
            std::cout << std::endl;
        }
        p++;
    }
}

// void Simulation::show_data()
// {
    
//     for (int i = 0; i < 30; ++i)
//     {
//         std::cout << "=";
//     }
//     std::cout << "DATA SEGMENT" << std::endl;
//     for (int i = 0; i < 30; ++i)
//     {
//         std::cout << "=";
//     }

//     std::cout << std::setw(13) << std::right
//               << "addr (int)|" << std::right
//               << "addr (hex)|" << std::right
//               << "value (int)|" << std::right
//               << "value (hex)|" << std::right
//               << "value (char)" << std::endl;
//     for (int i = 0; i < data.size(); ++i)
//     {
//         std::cout << std::setw(13) << std::right
//                   << data.addri(i, 4) << '|' << std::right
//                   << data.addrh(i, 4) << '|' << std::right
//                   << data.valuei(i, 4) << '|' << std::right
//                   << data.valueh(i, 4) << '|' << std::right
//                   << data.valuec(i, 4) << std::endl;
//     }
    
// }

// void Simulation::show_labels()
// {
//     for (int i = 0; i < 30; ++i)
//     {
//         std::cout << "=";
//     }
//     std::cout << "Labels" << std::endl;
//     for (int i = 0; i < 30; ++i)
//     {
//         std::cout << "=";
//     }

//     // TODO: show labels
// }
