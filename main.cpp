#include <iostream>
#include <cmath>
#include <limits>

unsigned char * uint_to_hexad(int32_t i);
unsigned char * uint_to_buff(int32_t i);
int32_t hexad_to_uint(unsigned char buff[]);
int32_t buff_to_int(unsigned char buff[]);

int main(int argc, char ** argv)
{
    std::vector<> 
    while (true)
    {
        // read string from keyboard and put into input array of characters
        char s[MAX_BUF];
        std::cout << ">>> ";
        std::cin.getline(s, MAX_BUF);
        if (std::cin.eof()) break;
        if (std::cin.fail() || std::cin.bad())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
        }
        std::cout << '[' << s << "]\n";

        std::vector<Words *> tok;
        Tokenize(s, tok);
        
    }
    
    return 0;
}
