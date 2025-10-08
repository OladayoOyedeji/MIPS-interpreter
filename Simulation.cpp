#include "Simulation.h"

bool token(const char * s)
{
    // int i = 0;
    // while (s[i] != '\0')
    // {
    //     std::cout << (s[i] == '\0') << std::endl;
    //     std::cout << int(s[i++]) << ',' << int('\0') << std::endl;;
    // }
    if (s == "" || s == "\n" || s[0] =='\0')
    {
        return false;
    }
    return true;
}

// void Simulation::read_file(const char * filename)
// {}

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

        if (token(s))
        {
        // tokenize instruction
        // and instruction can be divided into label, instruction and registers,
        // or instruction to be
        // Also if psuedo instruction divide into instructions
            text_.insert(s);
            
            i++;
        }
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
