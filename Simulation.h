#ifndef SIMULATION_H
#define SIMULATION_H

#include <cmath>
#include <limits>
#include "TextSegment.h"
#include "Register_File.h"
#include <filesystem>
#include <stdlib.h>

#ifdef _WIN32
#include <direct.h> // For _getcwd on Windows
#define GET_CURRENT_DIR _getcwd
#else
#include <unistd.h> // For getcwd on POSIX systems
#define GET_CURRENT_DIR getcwd
#endif

namespace fs = std::filesystem;

//bool tokenize(const char * s);

class Simulation
{
public:
    Simulation(const char * filename = "")
        : filename_(filename), HI_(0), LO_(0), PC_(TS_ADDRESS)
    {}
    void read_file();
    void display_curdir_files();
    int Robert_Language_lexer(const std::string & command, char * arg,
                               char * path, int &size);
    void run_sim(const char * filename = "");
    void print_option_message()
    {
        std::cout << "[t] Text segment\n"
                  << "[d] Data segment\n"
                  << "[?] Instruction manual\n"
                  << "[p] Print system\n"
                  << "[l] Load file" << std::endl;
    }
    // void save_to_file(const char * filename);
    void run_text();
    // void run_data();
    void show_reg() const;
    void print_system() const;
    // void show_data();
    void show_labels() const;
private:
    TextSegment text_;
    //DataSegment data_;
    //int mode_;
    RegisterFile registers_;
    std::map< std::string, uint32_t > label_;
    std::string filename_;
    uint32_t HI_;
    uint32_t LO_;
    uint32_t PC_;
};

#endif
