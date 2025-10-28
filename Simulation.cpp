#include "Simulation.h"

// bool tokenize(const std::string & s, std::list<std::string> & instructions,
//               char delim, int max_delim_deg)
// {
    
//     // remove trailing spaces, i tracks where non space starts
//     int i = 0;
//     while (s[i] == ' ')
//     {
//         if (s[i++] == '\0')
//         {
//             return false;
//         }
//     }

//     int j = i;
//     // put token it
//     int deg = 0;
//     while (s[j] != '\0' && deg < max_delim_deg)
//     {
//         if (s[j++] == ' ')
//         {
//             instructions.push_back(s.substr(i, j-i));
//             deg++;
//         }
        
//     }
//     return true;
// }
    // if (s == "" || s == "\n" || s[0] =='\0')
//     {
//         return false;
//     }
//     // remove trailing spaces, i tracks where non space starts
//     int i = 0;
//     while (s[i] == ' ')
//     {
//         if (s[i++] == '\0')
//         {
//             return false;
//         }
//     }
//     int start_ = i;
//     bool is_label;
//     while (s[i] != ' ')
//     {
//         if (s[i] == ':')
//         {
//             // push s.substr(start_, i) in the
//         }
//     }
//     return true;
// }

// state 1:go into a directory, state 0:file loaded, state -1:error in the syntax
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
        if (size == 0)
            std::cout << "mmmyeah\n";
        for (; size >= 0; --size)
        {
            if (path[size] == '/')
            {
                path[size] = '\0';
                return 1;
            }
        }
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
                std::cout << "here? " << instruction_state << std::endl;
                if (command[i] == ' ' || command[i] == '\t')
                {
                    i = j++;
                    continue;
                }
                std::cout << instruction_state << std::endl;
                if (instruction_state == 0)
                {
                    std::cout << '[' << command.substr(i, j-i) << ']' << std::endl;
                    if (strcmp(command.substr(i, j-i), "lf"))
                    {
                        std::cout << "load a file" << std::endl;
                        state = 0;
                    }
                    else if (strcmp(command.substr(i, j - i), "move"))
                    {
                        std::cout << "move into a directory" << std::endl;
                        state = 1;
                    }
                    else return -1;
                }
                else if (instruction_state == 1)
                {
                    std::cout << "step 2\n";
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
{}

void Simulation::display_curdir_files()
{
    char path[FILENAME_MAX];
    GET_CURRENT_DIR(path, sizeof(path));
    int size = len(path);
    int option = 1;
    int i = 0;
        
    while (option != 0)
    {
        std::cout << path << std::endl;
        // print files and directory in the directory
        for (const auto& entry : fs::directory_iterator(path))
        {
            // Check if the entry is a regular file
            if (fs::is_regular_file(entry.status()))
                std::cout << "\033[33;44m";
            else
                std::cout << "\033[1;37;40m";
            std::cout << entry.path().filename() << "\033[0m ";
            // Print only the filename
                
        }
        std::cout << "<-" << std::endl;

        // get a command
        char command[MAX_BUF] = "";
        std::cout << '[' << command << ']' << std::endl;
        std::cout << ">> ";
        std::cin.getline(command, MAX_BUF);
        if (std::cin.eof()) break;
        if (std::cin.fail() || std::cin.bad())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
        }
        char file[MAX_BUF] = "";
        int state = Robert_Language_lexer(command, file, path, size);
        //if (state )
        // instruction[3]
        // if ()
        std::cout << state << " [" << file << ']' << std::endl;;
        std::cout << i++ << std::endl;
        std::cout << "enter option" << std::endl;
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n');
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
        text_.insert(s);
            
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

// void Simulation::show_reg()
// {}

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
