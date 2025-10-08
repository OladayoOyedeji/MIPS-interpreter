#ifndef SIMULATION_H
#define SIMULATION_H

#include <cmath>
#include <limits>
#include "TextSegment.h"

bool token(char * s);

class Simulation
{
public:
    Simulation()
    {
        std::cout << "yo what is happening" << std::endl;
    }
    // void read_file(const char * name);
    void run_sim(const char * filename = "");
    void print_option_message()
    {
        std::cout << "[t] text segment\n"
                  << "[d] data segment\n"
                  << "[?] instruction manual\n"
                  << "[p] print system" << std::endl;
    }
    // void save_to_file(const char * filename);
    void run_text();
    // void run_data();
    // void show_reg();
    // void show_data();
    // void show_labels();
private:
    TextSegment text_;
    //DataSegment data_;
    //int mode_;
    //RegisterFile registers_;
    //Labels label_;
};

#endif
