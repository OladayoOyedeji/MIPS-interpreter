#include <iostream>

#include "Simulation.h"

int main(int argc, char ** argv)
{
    std::cout << argv[0] << std::endl;
    Simulation mips(argv[0]);
    mips.run_sim();
    
    return 0;
}
