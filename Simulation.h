#ifndef SIMULATION_H
#define SIMULATION_H

bool token(char * s);

class Simulation
{
public:
    void read_file(const char * name);
    void run_sim(const char * filename = "");
    void save_to_file(const char * filename);
    void run_text();
    void run_data();
    void show_reg();
    void show_data();
    void show_labels();
private:
    Textfile text_;
    DataFile data_;
    int mode_;
    RegisterFile registers_;
    Labels label_;
};

#endif
