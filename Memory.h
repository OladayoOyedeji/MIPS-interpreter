#ifndef MEMORY_H
#define MEMORY_H

class Memory
{
    Memory()
    {}
    
    std::map< uint32_t, std::string > mem_;
    unsigned char * data_;
};

#endif
