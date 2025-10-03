#ifndef TEXTFILE_H
#define TEXTFILE_H

class TextFile
{
public:
    TextFile();
    void print_addressh(int i);
    void insert(const char * s)
private:
    std::vector< std::string > instructions_;
    int32_t starting_address_;
};

#endif
