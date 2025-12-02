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
        : filename_(filename), PC_(TS_ADDRESS), data_(new unsigned char[1024]), data_segment_size_(0)
    {
        //const char  s[1024] = "hello world !!!!\n what is your name?";
        for (int i = 0; i < 100; ++i)
        {
            data_[i] = 0;
        }
    }
    void read_file();
    void display_curdir_files();
    int Robert_Language_lexer(const std::string & command, char * arg,
                               char * path, int &size);
    void run_sim(const char * filename = "");
    void print_option_message()
    {
        std::cout << "[s] Live simulation\n"
                  << "[?] Instruction manual\n"
                  << "[l] Load file" << std::endl;
    }
    // void save_to_file(const char * filename);
    void get_input(std::ifstream &, std::string &, bool break_, uint32_t address);
    int run_text(uint32_t &);
    int run_data();
    void show_reg() const;
    void show_data() const;
    void print_system() const;
    void show_labels() const;
    bool SignalException();
    void convert_to_machine_format(const std::vector< std::string >& v, int32_t machine_instruction[], uint32_t address);
    void insert_label(std::string & label, uint32_t address);
    int32_t get_label(const std::string & s, uint32_t address);
    void pseudo_to_instruction(const std::vector< std::string > & token, uint32_t & address);
    void process_token(const std::vector< std::string > & token,
                       uint32_t & address);
    void process_data_token(const std::vector< std::string > & token,
                            uint32_t address);
private:
    std::map< uint32_t, MachineFormat * > instruction_;
    unsigned char * data_;
    uint32_t data_segment_size_;
    //int mode_;
    RegisterFile registers_;
    
    std::map< std::string, uint32_t > label_;
    std::map< std::string, uint32_t > undefined_label_;
    
    std::string filename_;
    uint32_t PC_;
};

#endif
