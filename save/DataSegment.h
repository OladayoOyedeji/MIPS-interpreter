#ifndef DATAFILE_H
#define DATAFILE_H

class DataFile
{
public:
    DataFile(int32_t start_address);
    int32_t & operator[](int i);
    void addri(int i) const;
    void addrh(int i) const;
    void valuei(int i) const;
    void valueh(int i) const;
    void valuec(int i) const;
private:
    int32_t start_address_;
    int32_t * data_;
    int size_;
    const int max_size_;
};

#endif
