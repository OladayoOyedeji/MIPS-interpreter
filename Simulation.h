#ifndef SIMULATION_H
#define SIMULATION_H

#include <cmath>
#include <limits>
#include "Memory.h"
#include "Register_File.h"
namespace fs = std::filesystem;

//bool tokenize(const char * s);

class Simulation
{
public:
    Simulation(const char * filename)
        : PC_(TS_ADDRESS), filename_(filename)
    {
        char filepath[1024];
        filepath_ = GET_CURRENT_DIR(filepath, sizeof(filepath));
        
    }
    void read_file();
    void display_curdir_files();
    int Robert_Language_lexer(const std::string & command, char * arg);
    void reinitialize_sim();
    void run_sim(const char * filename = "");
    void print_option_message()
    {
        std::cout << "[s] Live simulation\n"
                  << "[?] Instruction manual\n"
                  << "[l] Load file" << std::endl;
    }
    void get_input(std::ifstream &, std::string &, bool & break_, uint32_t address, bool);
    int run_text(uint32_t &, std::ifstream * f=NULL);
    int run_data(std::ifstream * f=NULL);
    void show_reg() const;
    void show_data() const;
    void print_system() const;
    void show_labels() const;
    bool SignalException();
    void convert_to_machine_format(const std::vector< std::string >& v, 
                                   int32_t machine_instruction[], uint32_t address);
    void insert_label(std::string & label, uint32_t address);
    int32_t get_label(const std::string & s, uint32_t address);
    void pseudo_to_instruction(const std::vector< std::string > & token, uint32_t & address);
    void process_token(const std::vector< std::string > & token,
                       uint32_t & address);
    void process_data_token(const std::vector< std::string > & token,
                            uint32_t address);
private:
    Memory memory_;
    RegisterFile registers_;
    
    std::map< std::string, uint32_t > label_;
    std::map< std::string, std::list<uint32_t> > undefined_label_;
    
    std::string filepath_;

    std::string filename_;
    uint32_t PC_;
};

#endif
