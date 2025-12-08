#ifndef MEMORY_H
#define MEMORY_H

#include "Machine_Format.h"

class Memory
{
public:
    Memory(int32_t data_size=0, int32_t stack_size=0)
        : data_(new unsigned char[MAX_BUF]), stack_(new unsigned char[MAX_BUF]),
          data_size_(data_size), stack_size_(stack_size)
    {
        for (int i = 0; i < MAX_BUF; ++i)
        {
            data_[i] = 0;
            stack_[i] = 0;
        }
    }
    ~Memory();
    void init()
    {
        data_ = new unsigned char[MAX_BUF];
        stack_ = new unsigned char[MAX_BUF];
        
        for (int i = 0; i < MAX_BUF; ++i)
        {
            data_[i] = 0;
            stack_[i] = 0;
        }
    }
    void insert_instruction(uint32_t address, int32_t machine_instruction[], int i=0);
    void insert_imm(uint32_t key, uint32_t address);
    void insert_word_to_memory(uint32_t address, uint32_t d);
    void read_bytes_from_memory(uint32_t address, uint32_t & x, int size=4);
    void write_bytes_to_memory(uint32_t address, uint32_t x, int size=4);
    void write_bytes_to_memory(uint32_t address, const std::string & s);
    void write_a_byte_to_memory(uint32_t address, unsigned char c);
    void read_a_byte_from_memory(uint32_t address, unsigned char & c);
    unsigned char operator[](uint32_t address) const;
    unsigned char & operator[](uint32_t address);
    void clear();
    void write_to_a_file(std::string & filepath);
    void write_instruction_to_a_file(std::string & filepath);
    void write_data_to_a_file(std::string & filepath);
    int32_t data_size() const
    {
        return data_size_;
    }
    
    int32_t stack_size() const
    {
        return stack_size_;
    }
    void print_data(uint32_t ) const;
    void display_data() const;
    void execute_instruction(uint32_t & PC, RegisterFile & registers);
    
    std::map< uint32_t, MachineFormat * > instruction_;
    unsigned char * data_;
    int32_t data_size_;
    unsigned char * stack_;
    int32_t stack_size_;
};

void execute_code(MachineFormat & instruction, RegisterFile & r, uint32_t & PC, Memory & memory);

#endif
